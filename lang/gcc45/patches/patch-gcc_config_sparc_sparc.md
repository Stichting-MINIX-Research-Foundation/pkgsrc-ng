$NetBSD$

--- gcc/config/sparc/sparc.md.orig	Sun Dec 19 12:20:08 2010
+++ gcc/config/sparc/sparc.md
@@ -28,6 +28,7 @@
   [(UNSPEC_MOVE_PIC		0)
    (UNSPEC_UPDATE_RETURN	1)
    (UNSPEC_LOAD_PCREL_SYM	2)
+   (UNSPEC_FRAME_BLOCKAGE      3)
    (UNSPEC_MOVE_PIC_LABEL	5)
    (UNSPEC_SETH44		6)
    (UNSPEC_SETM44		7)
@@ -2477,11 +2478,9 @@
 			(match_operand:I 3 "arith10_operand" "")))]
   "TARGET_V9 && !(<I:MODE>mode == DImode && TARGET_ARCH32)"
 {
-  enum rtx_code code = GET_CODE (operands[1]);
   rtx cc_reg;
 
-  if (GET_MODE (XEXP (operands[1], 0)) == DImode
-      && ! TARGET_ARCH64)
+  if (GET_MODE (XEXP (operands[1], 0)) == DImode && !TARGET_ARCH64)
     FAIL;
 
   if (GET_MODE (XEXP (operands[1], 0)) == TFmode && !TARGET_HARD_QUAD)
@@ -2492,12 +2491,14 @@
   if (XEXP (operands[1], 1) == const0_rtx
       && GET_CODE (XEXP (operands[1], 0)) == REG
       && GET_MODE (XEXP (operands[1], 0)) == DImode
-      && v9_regcmp_p (code))
+      && v9_regcmp_p (GET_CODE (operands[1])))
     cc_reg = XEXP (operands[1], 0);
   else
     cc_reg = gen_compare_reg (operands[1]);
 
-  operands[1] = gen_rtx_fmt_ee (code, GET_MODE (cc_reg), cc_reg, const0_rtx);
+  operands[1]
+    = gen_rtx_fmt_ee (GET_CODE (operands[1]), GET_MODE (cc_reg), cc_reg,
+		      const0_rtx);
 })
 
 (define_expand "mov<F:mode>cc"
@@ -2507,11 +2508,9 @@
 			(match_operand:F 3 "register_operand" "")))]
   "TARGET_V9 && TARGET_FPU"
 {
-  enum rtx_code code = GET_CODE (operands[1]);
   rtx cc_reg;
 
-  if (GET_MODE (XEXP (operands[1], 0)) == DImode
-      && ! TARGET_ARCH64)
+  if (GET_MODE (XEXP (operands[1], 0)) == DImode && !TARGET_ARCH64)
     FAIL;
 
   if (GET_MODE (XEXP (operands[1], 0)) == TFmode && !TARGET_HARD_QUAD)
@@ -2522,12 +2521,14 @@
   if (XEXP (operands[1], 1) == const0_rtx
       && GET_CODE (XEXP (operands[1], 0)) == REG
       && GET_MODE (XEXP (operands[1], 0)) == DImode
-      && v9_regcmp_p (code))
+      && v9_regcmp_p (GET_CODE (operands[1])))
     cc_reg = XEXP (operands[1], 0);
   else
     cc_reg = gen_compare_reg (operands[1]);
 
-  operands[1] = gen_rtx_fmt_ee (code, GET_MODE (cc_reg), cc_reg, const0_rtx);
+  operands[1]
+    = gen_rtx_fmt_ee (GET_CODE (operands[1]), GET_MODE (cc_reg), cc_reg,
+		      const0_rtx);
 })
 
 ;; Conditional move define_insns
@@ -6315,9 +6316,7 @@
 			       (if_then_else (eq_attr "isa" "v9")
 					     (const_int 2)
 					     (const_int 3))
-			       (if_then_else (eq_attr "isa" "v9")
-					     (const_int 3)
-					     (const_int 4)))
+			       (const_int 4))
 	       (eq_attr "empty_delay_slot" "true")
 		 (if_then_else (eq_attr "delayed_branch" "true")
 			       (const_int 2)
@@ -6333,6 +6332,25 @@
   ""
   [(set_attr "length" "0")])
 
+;; Do not schedule instructions accessing memory before this point.
+
+(define_expand "frame_blockage"
+  [(set (match_dup 0)
+	(unspec:BLK [(match_dup 1)] UNSPEC_FRAME_BLOCKAGE))]
+  ""
+{
+  operands[0] = gen_rtx_MEM (BLKmode, gen_rtx_SCRATCH (Pmode));
+  MEM_VOLATILE_P (operands[0]) = 1;
+  operands[1] = stack_pointer_rtx;
+})
+
+(define_insn "*frame_blockage<P:mode>"
+  [(set (match_operand:BLK 0 "" "")
+	(unspec:BLK [(match_operand:P 1 "" "")] UNSPEC_FRAME_BLOCKAGE))]
+  ""
+  ""
+  [(set_attr "length" "0")])
+
 (define_expand "probe_stack"
   [(set (match_operand 0 "memory_operand" "") (const_int 0))]
   ""
@@ -6491,8 +6509,8 @@
 		      (const_int 4)))])
 
 ;; For __builtin_setjmp we need to flush register windows iff the function
-;; calls alloca as well, because otherwise the register window might be
-;; saved after %sp adjustment and thus setjmp would crash
+;; calls alloca as well, because otherwise the current register window might
+;; be saved after the %sp adjustment and thus setjmp would crash.
 (define_expand "builtin_setjmp_setup"
   [(match_operand 0 "register_operand" "r")]
   ""
@@ -6531,19 +6549,26 @@
                (eq_attr "pic" "true")
                  (const_int 4)] (const_int 3)))])
 
-;; Pattern for use after a setjmp to store FP and the return register
-;; into the stack area.
+;; Pattern for use after a setjmp to store registers into the save area.
 
 (define_expand "setjmp"
   [(const_int 0)]
   ""
 {
   rtx mem;
-  
+
+  if (flag_pic)
+    {
+      mem = gen_rtx_MEM (Pmode,
+			 plus_constant (stack_pointer_rtx,
+					SPARC_STACK_BIAS + 7 * UNITS_PER_WORD));
+      emit_insn (gen_rtx_SET (VOIDmode, mem, pic_offset_table_rtx));
+    }
+
   mem = gen_rtx_MEM (Pmode,
 		     plus_constant (stack_pointer_rtx,
 				    SPARC_STACK_BIAS + 14 * UNITS_PER_WORD));
-  emit_insn (gen_rtx_SET (VOIDmode, mem, frame_pointer_rtx));
+  emit_insn (gen_rtx_SET (VOIDmode, mem, hard_frame_pointer_rtx));
 
   mem = gen_rtx_MEM (Pmode,
 		     plus_constant (stack_pointer_rtx,
