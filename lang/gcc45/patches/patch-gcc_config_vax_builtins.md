$NetBSD$

--- gcc/config/vax/builtins.md.orig	Wed Apr  1 17:00:00 2009
+++ gcc/config/vax/builtins.md
@@ -24,6 +24,12 @@
   ]
 )
 
+(define_expand "condjump"
+  [(set (pc)
+	(if_then_else (match_operand 0)
+		      (label_ref (match_operand 1))
+		      (pc)))])
+
 (define_expand "ffssi2"
   [(set (match_operand:SI 0 "nonimmediate_operand" "")
 	(ffs:SI (match_operand:SI 1 "general_operand" "")))]
@@ -32,7 +38,7 @@
 {
   rtx label = gen_label_rtx ();
   emit_insn (gen_ffssi2_internal (operands[0], operands[1]));
-  emit_jump_insn (gen_bne (label));
+  emit_jump_insn (gen_condjump (gen_rtx_NE(VOIDmode, cc0_rtx, const0_rtx), label));
   emit_insn (gen_negsi2 (operands[0], const1_rtx));
   emit_label (label);
   emit_insn (gen_addsi3 (operands[0], operands[0], const1_rtx));
@@ -189,4 +195,3 @@
 	  (const_int 0))])]
   ""
   "jbcci %1,%0,%l2")
-
