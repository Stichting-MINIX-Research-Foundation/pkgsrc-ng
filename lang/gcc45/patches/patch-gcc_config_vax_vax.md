$NetBSD$

--- gcc/config/vax/vax.md.orig	Tue May 12 09:43:48 2009
+++ gcc/config/vax/vax.md
@@ -212,6 +212,11 @@
   ""
   "
 {
+  if (CONST_INT_P (operands[2]) && INTVAL (operands[2]) <= 48)
+    {
+      emit_insn (gen_movmemsi1_2 (operands[0], operands[1], operands[2]));
+      DONE;
+    }
   emit_insn (gen_movmemhi1 (operands[0], operands[1], operands[2]));
   DONE;
 }")
@@ -221,6 +226,13 @@
 ;; that anything generated as this insn will be recognized as one
 ;; and that it won't successfully combine with anything.
 
+(define_insn "movmemsi1_2"
+  [(set (match_operand:BLK 0 "memory_operand" "=B")
+	(match_operand:BLK 1 "memory_operand" "B"))
+   (use (match_operand:SI 2 "const_int_operand" "g"))]
+  "INTVAL (operands[2]) <= 48"
+  "* return vax_output_movmemsi (insn, operands);")
+
 (define_insn "movmemhi1"
   [(set (match_operand:BLK 0 "memory_operand" "=o")
 	(match_operand:BLK 1 "memory_operand" "o"))
@@ -625,7 +637,7 @@
   ""
   "
 {
-  if (! CONST_INT_P(operands[2]))
+  if (! CONST_INT_P (operands[2]))
     operands[2] = gen_rtx_NEG (QImode, negate_rtx (QImode, operands[2]));
 }")
 
@@ -689,14 +701,14 @@
 	(ashift:DI (match_operand:DI 1 "general_operand" "g")
 		   (match_operand:QI 2 "general_operand" "g")))]
   ""
-  "ashq %2,%1,%0")
+  "ashq %2,%D1,%0")
 
 (define_insn ""
   [(set (match_operand:DI 0 "nonimmediate_operand" "=g")
 	(ashiftrt:DI (match_operand:DI 1 "general_operand" "g")
 		     (neg:QI (match_operand:QI 2 "general_operand" "g"))))]
   ""
-  "ashq %2,%1,%0")
+  "ashq %2,%D1,%0")
 
 ;; We used to have expand_shift handle logical right shifts by using extzv,
 ;; but this make it very difficult to do lshrdi3.  Since the VAX is the
@@ -945,8 +957,8 @@
   ""
   "*
 {
-  if (!REG_P (operands[0]) || !CONST_INT_P (operands[2])
-      || !CONST_INT_P (operands[3])
+  if (! REG_P (operands[0]) || ! CONST_INT_P (operands[2])
+      || ! CONST_INT_P (operands[3])
       || (INTVAL (operands[2]) != 8 && INTVAL (operands[2]) != 16)
       || INTVAL (operands[2]) + INTVAL (operands[3]) > 32
       || side_effects_p (operands[1])
@@ -974,8 +986,8 @@
   ""
   "*
 {
-  if (!REG_P (operands[0]) || !CONST_INT_P (operands[2])
-      || !CONST_INT_P (operands[3])
+  if (! REG_P (operands[0]) || ! CONST_INT_P (operands[2])
+      || ! CONST_INT_P (operands[3])
       || INTVAL (operands[2]) + INTVAL (operands[3]) > 32
       || side_effects_p (operands[1])
       || (MEM_P (operands[1])
@@ -1634,3 +1646,5 @@
   emit_barrier ();
   DONE;
 })
+
+(include "builtins.md")
