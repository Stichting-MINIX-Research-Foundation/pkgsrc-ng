$NetBSD$

--- gcc/config/i386/i386.c.orig	Thu Feb 17 21:22:02 2011
+++ gcc/config/i386/i386.c
@@ -46,6 +46,7 @@ along with GCC; see the file COPYING3.  If not see
 #include "target.h"
 #include "target-def.h"
 #include "langhooks.h"
+#include "reload.h"
 #include "cgraph.h"
 #include "gimple.h"
 #include "dwarf2.h"
@@ -1540,7 +1541,7 @@ unsigned char ix86_arch_features[X86_ARCH_LAST];
 /* Feature tests against the various architecture variations, used to create
    ix86_arch_features based on the processor mask.  */
 static unsigned int initial_ix86_arch_features[X86_ARCH_LAST] = {
-  /* X86_ARCH_CMOVE: Conditional move was added for pentiumpro.  */
+  /* X86_ARCH_CMOV: Conditional move was added for pentiumpro.  */
   ~(m_386 | m_486 | m_PENT | m_K6),
 
   /* X86_ARCH_CMPXCHG: Compare and exchange was added for 80486.  */
@@ -3071,7 +3072,7 @@ override_options (bool main_args_p)
 	   -mtune (rather than -march) points us to a processor that has them.
 	   However, the VIA C3 gives a SIGILL, so we only do that for i686 and
 	   higher processors.  */
-	if (TARGET_CMOVE
+	if (TARGET_CMOV
 	    && (processor_alias_table[i].flags & (PTA_PREFETCH_SSE | PTA_SSE)))
 	  x86_prefetch_sse = true;
 	break;
@@ -3400,11 +3401,6 @@ override_options (bool main_args_p)
       target_flags |= MASK_ACCUMULATE_OUTGOING_ARGS;
     }
 
-  /* For sane SSE instruction set generation we need fcomi instruction.
-     It is safe to enable all CMOVE instructions.  */
-  if (TARGET_SSE)
-    TARGET_CMOVE = 1;
-
   /* Figure out what ASM_GENERATE_INTERNAL_LABEL builds as a prefix.  */
   {
     char *p;
@@ -9875,6 +9871,64 @@ legitimate_pic_address_disp_p (rtx disp)
   return 0;
 }
 
+/* Our implementation of LEGITIMIZE_RELOAD_ADDRESS.  Returns a value to
+   replace the input X, or the original X if no replacement is called for.
+   The output parameter *WIN is 1 if the calling macro should goto WIN,
+   0 if it should not.  */
+
+bool
+ix86_legitimize_reload_address (rtx x,
+				enum machine_mode mode ATTRIBUTE_UNUSED,
+				int opnum, int type,
+				int ind_levels ATTRIBUTE_UNUSED)
+{
+  /* Reload can generate:
+
+     (plus:DI (plus:DI (unspec:DI [(const_int 0 [0])] UNSPEC_TP)
+		       (reg:DI 97))
+	      (reg:DI 2 cx))
+
+     This RTX is rejected from ix86_legitimate_address_p due to
+     non-strictness of base register 97.  Following this rejection, 
+     reload pushes all three components into separate registers,
+     creating invalid memory address RTX.
+
+     Following code reloads only the invalid part of the
+     memory address RTX.  */
+
+  if (GET_CODE (x) == PLUS
+      && REG_P (XEXP (x, 1))
+      && GET_CODE (XEXP (x, 0)) == PLUS
+      && REG_P (XEXP (XEXP (x, 0), 1)))
+    {
+      rtx base, index;
+      bool something_reloaded = false;
+
+      base = XEXP (XEXP (x, 0), 1);      
+      if (!REG_OK_FOR_BASE_STRICT_P (base))
+	{
+	  push_reload (base, NULL_RTX, &XEXP (XEXP (x, 0), 1), NULL,
+		       BASE_REG_CLASS, GET_MODE (x), VOIDmode, 0, 0,
+		       opnum, (enum reload_type)type);
+	  something_reloaded = true;
+	}
+
+      index = XEXP (x, 1);
+      if (!REG_OK_FOR_INDEX_STRICT_P (index))
+	{
+	  push_reload (index, NULL_RTX, &XEXP (x, 1), NULL,
+		       INDEX_REG_CLASS, GET_MODE (x), VOIDmode, 0, 0,
+		       opnum, (enum reload_type)type);
+	  something_reloaded = true;
+	}
+
+      gcc_assert (something_reloaded);
+      return true;
+    }
+
+  return false;
+}
+
 /* Recognizes RTL expressions that are valid memory addresses for an
    instruction.  The MODE argument is the machine mode for the MEM
    expression that wants to use this address.
@@ -11872,6 +11926,13 @@ print_operand (FILE *file, rtx x, int code)
 	  return;
 
 	case 'H':
+	  if (!offsettable_memref_p (x))
+	    {
+	      output_operand_lossage ("operand is not an offsettable memory "
+				      "reference, invalid operand "
+				      "code 'H'");
+	      return;
+	    }
 	  /* It doesn't actually matter what mode we use here, as we're
 	     only going to use this for printing.  */
 	  x = adjust_address_nv (x, DImode, 8);
@@ -14610,11 +14671,15 @@ ix86_match_ccmode (rtx insn, enum machine_mode req_mod
       if (req_mode == CCZmode)
 	return 0;
       /* FALLTHRU */
+    case CCZmode:
+      break;
+
     case CCAmode:
     case CCCmode:
     case CCOmode:
     case CCSmode:
-    case CCZmode:
+      if (set_mode != req_mode)
+	return 0;
       break;
 
     default:
@@ -16196,11 +16261,15 @@ ix86_expand_sse_movcc (rtx dest, rtx cmp, rtx op_true,
     }
   else if (TARGET_XOP)
     {
-      rtx pcmov = gen_rtx_SET (mode, dest,
-			       gen_rtx_IF_THEN_ELSE (mode, cmp,
-						     op_true,
-						     op_false));
-      emit_insn (pcmov);
+      op_true = force_reg (mode, op_true);
+
+      if (!nonimmediate_operand (op_false, mode))
+	op_false = force_reg (mode, op_false);
+
+      emit_insn (gen_rtx_SET (mode, dest,
+			      gen_rtx_IF_THEN_ELSE (mode, cmp,
+						    op_true,
+						    op_false)));
     }
   else
     {
@@ -20104,7 +20173,9 @@ ix86_local_alignment (tree exp, enum machine_mode mode
   if (!TARGET_64BIT
       && align == 64
       && ix86_preferred_stack_boundary < 64
-      && (mode == DImode || (type && TYPE_MODE (type) == DImode))
+      && (mode == DImode || (type && TYPE_MODE (type) == DImode)
+          || mode == DFmode || (type && TYPE_MODE (type) == DFmode)
+          || mode == DCmode || (type && TYPE_MODE (type) == DCmode))
       && (!type || !TYPE_USER_ALIGN (type))
       && (!decl || !DECL_USER_ALIGN (decl)))
     align = 32;
@@ -20150,7 +20221,8 @@ ix86_local_alignment (tree exp, enum machine_mode mode
 	    || TREE_CODE (type) == QUAL_UNION_TYPE)
 	   && TYPE_FIELDS (type))
     {
-      if (DECL_MODE (TYPE_FIELDS (type)) == DFmode && align < 64)
+      if (DECL_MODE (TYPE_FIELDS (type)) == DFmode && align < 64
+          && ix86_preferred_stack_boundary >= 64)
 	return 64;
       if (ALIGN_MODE_128 (DECL_MODE (TYPE_FIELDS (type))) && align < 128)
 	return 128;
@@ -20159,7 +20231,8 @@ ix86_local_alignment (tree exp, enum machine_mode mode
 	   || TREE_CODE (type) == INTEGER_TYPE)
     {
 
-      if (TYPE_MODE (type) == DFmode && align < 64)
+      if (TYPE_MODE (type) == DFmode && align < 64
+          && ix86_preferred_stack_boundary >= 64)
 	return 64;
       if (ALIGN_MODE_128 (TYPE_MODE (type)) && align < 128)
 	return 128;
@@ -23991,8 +24064,8 @@ ix86_expand_special_args_builtin (const struct builtin
       arg_adjust = 0;
       if (optimize
 	  || target == 0
-	  || GET_MODE (target) != tmode
-	  || ! (*insn_p->operand[0].predicate) (target, tmode))
+	  || !register_operand (target, tmode)
+	  || GET_MODE (target) != tmode)
 	target = gen_reg_rtx (tmode);
     }
 
@@ -25067,7 +25140,7 @@ ix86_preferred_reload_class (rtx x, enum reg_class reg
 	 zero above.  We only want to wind up preferring 80387 registers if
 	 we plan on doing computation with them.  */
       if (TARGET_80387
-	  && standard_80387_constant_p (x))
+	  && standard_80387_constant_p (x) > 0)
 	{
 	  /* Limit class to non-sse.  */
 	  if (regclass == FLOAT_SSE_REGS)
@@ -27711,10 +27784,19 @@ ix86_expand_vector_set (bool mmx_ok, rtx target, rtx v
       break;
 
     case V2DImode:
-      use_vec_merge = TARGET_SSE4_1;
+      use_vec_merge = TARGET_SSE4_1 && TARGET_64BIT;
       if (use_vec_merge)
 	break;
 
+      tmp = gen_reg_rtx (GET_MODE_INNER (mode));
+      ix86_expand_vector_extract (false, tmp, target, 1 - elt);
+      if (elt == 0)
+	tmp = gen_rtx_VEC_CONCAT (mode, tmp, val);
+      else
+	tmp = gen_rtx_VEC_CONCAT (mode, val, tmp);
+      emit_insn (gen_rtx_SET (VOIDmode, target, tmp));
+      return;
+
     case V2DFmode:
       {
 	rtx op0, op1;
@@ -30651,6 +30733,11 @@ ix86_enum_va_list (int idx, const char **pname, tree *
 
 #undef TARGET_ASM_CODE_END
 #define TARGET_ASM_CODE_END ix86_code_end
+
+#if TARGET_MACHO
+#undef TARGET_INIT_LIBFUNCS
+#define TARGET_INIT_LIBFUNCS darwin_rename_builtins
+#endif
 
 struct gcc_target targetm = TARGET_INITIALIZER;
 
