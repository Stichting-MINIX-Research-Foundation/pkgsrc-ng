$NetBSD$

--- gcc/expr.c.orig	Sun Jan 16 20:23:01 2011
+++ gcc/expr.c
@@ -2220,6 +2220,111 @@ copy_blkmode_from_reg (rtx tgtblk, rtx srcreg, tree ty
   return tgtblk;
 }
 
+/* Copy BLKmode value SRC into a register of mode MODE.  Return the
+   register if it contains any data, otherwise return null.
+
+   This is used on targets that return BLKmode values in registers.  */
+
+rtx
+copy_blkmode_to_reg (enum machine_mode mode, tree src)
+{
+  int i, n_regs;
+  unsigned HOST_WIDE_INT bitpos, xbitpos, padding_correction = 0, bytes;
+  unsigned int bitsize;
+  rtx *dst_words, dst, x, src_word = NULL_RTX, dst_word = NULL_RTX;
+  enum machine_mode dst_mode;
+
+  gcc_assert (TYPE_MODE (TREE_TYPE (src)) == BLKmode);
+
+  x = expand_normal (src);
+
+  bytes = int_size_in_bytes (TREE_TYPE (src));
+  if (bytes == 0)
+    return NULL_RTX;
+
+  /* If the structure doesn't take up a whole number of words, see
+     whether the register value should be padded on the left or on
+     the right.  Set PADDING_CORRECTION to the number of padding
+     bits needed on the left side.
+
+     In most ABIs, the structure will be returned at the least end of
+     the register, which translates to right padding on little-endian
+     targets and left padding on big-endian targets.  The opposite
+     holds if the structure is returned at the most significant
+     end of the register.  */
+  if (bytes % UNITS_PER_WORD != 0
+      && (targetm.calls.return_in_msb (TREE_TYPE (src))
+	  ? !BYTES_BIG_ENDIAN
+	  : BYTES_BIG_ENDIAN))
+    padding_correction = (BITS_PER_WORD - ((bytes % UNITS_PER_WORD)
+					   * BITS_PER_UNIT));
+
+  n_regs = (bytes + UNITS_PER_WORD - 1) / UNITS_PER_WORD;
+  dst_words = XALLOCAVEC (rtx, n_regs);
+  bitsize = MIN (TYPE_ALIGN (TREE_TYPE (src)), BITS_PER_WORD);
+
+  /* Copy the structure BITSIZE bits at a time.  */
+  for (bitpos = 0, xbitpos = padding_correction;
+       bitpos < bytes * BITS_PER_UNIT;
+       bitpos += bitsize, xbitpos += bitsize)
+    {
+      /* We need a new destination pseudo each time xbitpos is
+	 on a word boundary and when xbitpos == padding_correction
+	 (the first time through).  */
+      if (xbitpos % BITS_PER_WORD == 0
+	  || xbitpos == padding_correction)
+	{
+	  /* Generate an appropriate register.  */
+	  dst_word = gen_reg_rtx (word_mode);
+	  dst_words[xbitpos / BITS_PER_WORD] = dst_word;
+
+	  /* Clear the destination before we move anything into it.  */
+	  emit_move_insn (dst_word, CONST0_RTX (word_mode));
+	}
+
+      /* We need a new source operand each time bitpos is on a word
+	 boundary.  */
+      if (bitpos % BITS_PER_WORD == 0)
+	src_word = operand_subword_force (x, bitpos / BITS_PER_WORD, BLKmode);
+
+      /* Use bitpos for the source extraction (left justified) and
+	 xbitpos for the destination store (right justified).  */
+      store_bit_field (dst_word, bitsize, xbitpos % BITS_PER_WORD, word_mode,
+		       extract_bit_field (src_word, bitsize,
+					  bitpos % BITS_PER_WORD, 1,
+					  NULL_RTX, word_mode, word_mode));
+    }
+
+  if (mode == BLKmode)
+    {
+      /* Find the smallest integer mode large enough to hold the
+	 entire structure.  */
+      for (mode = GET_CLASS_NARROWEST_MODE (MODE_INT);
+	   mode != VOIDmode;
+	   mode = GET_MODE_WIDER_MODE (mode))
+	/* Have we found a large enough mode?  */
+	if (GET_MODE_SIZE (mode) >= bytes)
+	  break;
+
+      /* A suitable mode should have been found.  */
+      gcc_assert (mode != VOIDmode);
+    }
+
+  if (GET_MODE_SIZE (mode) < GET_MODE_SIZE (word_mode))
+    dst_mode = word_mode;
+  else
+    dst_mode = mode;
+  dst = gen_reg_rtx (dst_mode);
+
+  for (i = 0; i < n_regs; i++)
+    emit_move_insn (operand_subword (dst, i, 0, dst_mode), dst_words[i]);
+
+  if (mode != dst_mode)
+    dst = gen_lowpart (mode, dst);
+
+  return dst;
+}
+
 /* Add a USE expression for REG to the (possibly empty) list pointed
    to by CALL_FUSAGE.  REG must denote a hard register.  */
 
@@ -3764,7 +3869,8 @@ emit_push_insn (rtx x, enum machine_mode mode, tree ty
   xinner = x;
 
   if (mode == BLKmode
-      || (STRICT_ALIGNMENT && align < GET_MODE_ALIGNMENT (mode)))
+      || (STRICT_ALIGNMENT && align < GET_MODE_ALIGNMENT (mode)
+	  && type != NULL_TREE))
     {
       /* Copy a block into the stack, entirely or partially.  */
 
@@ -4380,7 +4486,9 @@ expand_assignment (tree to, tree from, bool nontempora
   if (TREE_CODE (from) == CALL_EXPR && ! aggregate_value_p (from, from)
       && COMPLETE_TYPE_P (TREE_TYPE (from))
       && TREE_CODE (TYPE_SIZE (TREE_TYPE (from))) == INTEGER_CST
-      && ! (((TREE_CODE (to) == VAR_DECL || TREE_CODE (to) == PARM_DECL)
+      && ! (((TREE_CODE (to) == VAR_DECL
+	      || TREE_CODE (to) == PARM_DECL
+	      || TREE_CODE (to) == RESULT_DECL)
 	     && REG_P (DECL_RTL (to)))
 	    || TREE_CODE (to) == SSA_NAME))
     {
@@ -4426,12 +4534,15 @@ expand_assignment (tree to, tree from, bool nontempora
       rtx temp;
 
       push_temp_slots ();
-      temp = expand_expr (from, NULL_RTX, GET_MODE (to_rtx), EXPAND_NORMAL);
+      if (REG_P (to_rtx) && TYPE_MODE (TREE_TYPE (from)) == BLKmode)
+	temp = copy_blkmode_to_reg (GET_MODE (to_rtx), from);
+      else
+	temp = expand_expr (from, NULL_RTX, GET_MODE (to_rtx), EXPAND_NORMAL);
 
       if (GET_CODE (to_rtx) == PARALLEL)
 	emit_group_load (to_rtx, temp, TREE_TYPE (from),
 			 int_size_in_bytes (TREE_TYPE (from)));
-      else
+      else if (temp)
 	emit_move_insn (to_rtx, temp);
 
       preserve_temp_slots (to_rtx);
@@ -6906,6 +7017,14 @@ expand_expr_addr_expr_1 (tree exp, rtx target, enum ma
 				modifier == EXPAND_INITIALIZER
 				? EXPAND_INITIALIZER : EXPAND_CONST_ADDRESS);
 
+	  if (TREE_ADDRESSABLE (exp)
+	      && ! MEM_P (result)
+	      && ! targetm.calls.allocate_stack_slots_for_args ())
+	    {
+	      error ("local frame unavailable (naked function?)");
+	      return result;
+	    }
+
 	  /* If the DECL isn't in memory, then the DECL wasn't properly
 	     marked TREE_ADDRESSABLE, which will be either a front-end
 	     or a tree optimizer bug.  */
@@ -8144,7 +8263,10 @@ expand_expr_real_2 (sepops ops, rtx target, enum machi
       op1 = gen_label_rtx ();
       jumpifnot_1 (code, treeop0, treeop1, op1, -1);
 
-      emit_move_insn (target, const1_rtx);
+      if (TYPE_PRECISION (type) == 1 && !TYPE_UNSIGNED (type))
+	emit_move_insn (target, constm1_rtx);
+      else
+	emit_move_insn (target, const1_rtx);
 
       emit_label (op1);
       return target;
@@ -8517,11 +8639,15 @@ expand_expr_real_1 (tree exp, rtx target, enum machine
 	  return temp;
 	}
 
-      /* If the mode of DECL_RTL does not match that of the decl, it
-	 must be a promoted value.  We return a SUBREG of the wanted mode,
-	 but mark it so that we know that it was already extended.  */
+      /* If the mode of DECL_RTL does not match that of the decl,
+	 there are two cases: we are dealing with a BLKmode value
+	 that is returned in a register, or we are dealing with
+	 a promoted value.  In the latter case, return a SUBREG
+	 of the wanted mode, but mark it so that we know that it
+	 was already extended.  */
 
       if (REG_P (decl_rtl)
+	  && DECL_MODE (exp) != BLKmode
 	  && GET_MODE (decl_rtl) != DECL_MODE (exp))
 	{
 	  enum machine_mode pmode;
@@ -10036,7 +10162,8 @@ do_store_flag (sepops ops, rtx target, enum machine_mo
 
   if ((code == NE || code == EQ)
       && TREE_CODE (arg0) == BIT_AND_EXPR && integer_zerop (arg1)
-      && integer_pow2p (TREE_OPERAND (arg0, 1)))
+      && integer_pow2p (TREE_OPERAND (arg0, 1))
+      && (TYPE_PRECISION (ops->type) != 1 || TYPE_UNSIGNED (ops->type)))
     {
       tree type = lang_hooks.types.type_for_mode (mode, unsignedp);
       return expand_expr (fold_single_bit_test (loc,
@@ -10056,7 +10183,9 @@ do_store_flag (sepops ops, rtx target, enum machine_mo
 
   /* Try a cstore if possible.  */
   return emit_store_flag_force (target, code, op0, op1,
-			        operand_mode, unsignedp, 1);
+				operand_mode, unsignedp,
+				(TYPE_PRECISION (ops->type) == 1
+				 && !TYPE_UNSIGNED (ops->type)) ? -1 : 1);
 }
 
 
