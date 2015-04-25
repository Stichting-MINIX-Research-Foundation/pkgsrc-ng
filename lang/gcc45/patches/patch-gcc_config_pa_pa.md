$NetBSD$

--- gcc/config/pa/pa.md.orig	Thu Dec 30 21:57:32 2010
+++ gcc/config/pa/pa.md
@@ -811,7 +811,7 @@
 			 (match_operand:DI 3 "arith11_operand" "rI"))
 		 (match_operand:DI 1 "register_operand" "r")))]
   "TARGET_64BIT"
-  "sub%I3,* %3,%2,%%r0\;add,dc %%r0,%1,%0"
+  "sub%I3 %3,%2,%%r0\;add,dc %%r0,%1,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -833,7 +833,7 @@
 			 (match_operand:DI 3 "register_operand" "r"))
 		 (match_operand:DI 1 "register_operand" "r")))]
   "TARGET_64BIT"
-  "sub,* %2,%3,%%r0\;add,dc %%r0,%1,%0"
+  "sub %2,%3,%%r0\;add,dc %%r0,%1,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -856,7 +856,7 @@
 			 (match_operand:DI 3 "int11_operand" "I"))
 		 (match_operand:DI 1 "register_operand" "r")))]
   "TARGET_64BIT"
-  "addi,* %k3,%2,%%r0\;add,dc %%r0,%1,%0"
+  "addi %k3,%2,%%r0\;add,dc %%r0,%1,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -902,7 +902,7 @@
 		  (gtu:DI (match_operand:DI 2 "register_operand" "r")
 			  (match_operand:DI 3 "arith11_operand" "rI"))))]
   "TARGET_64BIT"
-  "sub%I3,* %3,%2,%%r0\;sub,db %1,%%r0,%0"
+  "sub%I3 %3,%2,%%r0\;sub,db %1,%%r0,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -924,7 +924,7 @@
 				    (match_operand:DI 3 "arith11_operand" "rI")))
 		  (match_operand:DI 4 "register_operand" "r")))]
   "TARGET_64BIT"
-  "sub%I3,* %3,%2,%%r0\;sub,db %1,%4,%0"
+  "sub%I3 %3,%2,%%r0\;sub,db %1,%4,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -946,7 +946,7 @@
 		  (ltu:DI (match_operand:DI 2 "register_operand" "r")
 			  (match_operand:DI 3 "register_operand" "r"))))]
   "TARGET_64BIT"
-  "sub,* %2,%3,%%r0\;sub,db %1,%%r0,%0"
+  "sub %2,%3,%%r0\;sub,db %1,%%r0,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -968,7 +968,7 @@
 				    (match_operand:DI 3 "register_operand" "r")))
 		  (match_operand:DI 4 "register_operand" "r")))]
   "TARGET_64BIT"
-  "sub,* %2,%3,%%r0\;sub,db %1,%4,%0"
+  "sub %2,%3,%%r0\;sub,db %1,%4,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -991,7 +991,7 @@
 		  (leu:DI (match_operand:DI 2 "register_operand" "r")
 			  (match_operand:DI 3 "int11_operand" "I"))))]
   "TARGET_64BIT"
-  "addi,* %k3,%2,%%r0\;sub,db %1,%%r0,%0"
+  "addi %k3,%2,%%r0\;sub,db %1,%%r0,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -1013,7 +1013,7 @@
 				    (match_operand:DI 3 "int11_operand" "I")))
 		  (match_operand:DI 4 "register_operand" "r")))]
   "TARGET_64BIT"
-  "addi,* %k3,%2,%%r0\;sub,db %1,%4,%0"
+  "addi %k3,%2,%%r0\;sub,db %1,%4,%0"
   [(set_attr "type" "binary")
    (set_attr "length" "8")])
 
@@ -5686,7 +5686,7 @@
 (define_expand "iordi3"
   [(set (match_operand:DI 0 "register_operand" "")
 	(ior:DI (match_operand:DI 1 "register_operand" "")
-		(match_operand:DI 2 "ior_operand" "")))]
+		(match_operand:DI 2 "reg_or_cint_ior_operand" "")))]
   ""
   "
 {
@@ -5707,7 +5707,7 @@
 (define_insn ""
   [(set (match_operand:DI 0 "register_operand" "=r,r")
 	(ior:DI (match_operand:DI 1 "register_operand" "0,0")
-		(match_operand:DI 2 "ior_operand" "M,i")))]
+		(match_operand:DI 2 "cint_ior_operand" "M,i")))]
   "TARGET_64BIT"
   "* return output_64bit_ior (operands); "
   [(set_attr "type" "binary,shift")
@@ -5726,19 +5726,14 @@
 (define_expand "iorsi3"
   [(set (match_operand:SI 0 "register_operand" "")
 	(ior:SI (match_operand:SI 1 "register_operand" "")
-		(match_operand:SI 2 "arith32_operand" "")))]
+		(match_operand:SI 2 "reg_or_cint_ior_operand" "")))]
   ""
-  "
-{
-  if (! (ior_operand (operands[2], SImode)
-         || register_operand (operands[2], SImode)))
-    operands[2] = force_reg (SImode, operands[2]);
-}")
+  "")
 
 (define_insn ""
   [(set (match_operand:SI 0 "register_operand" "=r,r")
 	(ior:SI (match_operand:SI 1 "register_operand" "0,0")
-		(match_operand:SI 2 "ior_operand" "M,i")))]
+		(match_operand:SI 2 "cint_ior_operand" "M,i")))]
   ""
   "* return output_ior (operands); "
   [(set_attr "type" "binary,shift")
@@ -6566,7 +6561,7 @@
   ""
   "*
 {
-  int x = INTVAL (operands[1]);
+  unsigned HOST_WIDE_INT x = UINTVAL (operands[1]);
   operands[2] = GEN_INT (4 + exact_log2 ((x >> 4) + 1));
   operands[1] = GEN_INT ((x & 0xf) - 0x10);
   return \"{zvdepi %1,%2,%0|depwi,z %1,%%sar,%2,%0}\";
@@ -6584,7 +6579,7 @@
   "exact_log2 (INTVAL (operands[1]) + 1) > 0"
   "*
 {
-  int x = INTVAL (operands[1]);
+  HOST_WIDE_INT x = INTVAL (operands[1]);
   operands[2] = GEN_INT (exact_log2 (x + 1));
   return \"{vdepi -1,%2,%0|depwi -1,%%sar,%2,%0}\";
 }"
@@ -6601,7 +6596,7 @@
   "INTVAL (operands[1]) == -2"
   "*
 {
-  int x = INTVAL (operands[1]);
+  HOST_WIDE_INT x = INTVAL (operands[1]);
   operands[2] = GEN_INT (exact_log2 ((~x) + 1));
   return \"{vdepi 0,%2,%0|depwi 0,%%sar,%2,%0}\";
 }"
@@ -6665,7 +6660,7 @@
   "TARGET_64BIT"
   "*
 {
-  int x = INTVAL (operands[1]);
+  unsigned HOST_WIDE_INT x = UINTVAL (operands[1]);
   operands[2] = GEN_INT (4 + exact_log2 ((x >> 4) + 1));
   operands[1] = GEN_INT ((x & 0x1f) - 0x20);
   return \"depdi,z %1,%%sar,%2,%0\";
@@ -6683,7 +6678,7 @@
   "TARGET_64BIT && exact_log2 (INTVAL (operands[1]) + 1) > 0"
   "*
 {
-  int x = INTVAL (operands[1]);
+  HOST_WIDE_INT x = INTVAL (operands[1]);
   operands[2] = GEN_INT (exact_log2 (x + 1));
   return \"depdi -1,%%sar,%2,%0\";
 }"
@@ -6700,7 +6695,7 @@
   "TARGET_64BIT && INTVAL (operands[1]) == -2"
   "*
 {
-  int x = INTVAL (operands[1]);
+  HOST_WIDE_INT x = INTVAL (operands[1]);
   operands[2] = GEN_INT (exact_log2 ((~x) + 1));
   return \"depdi 0,%%sar,%2,%0\";
 }"
@@ -7131,7 +7126,7 @@
     {
       rtx index = gen_reg_rtx (SImode);
 
-      operands[1] = GEN_INT (-INTVAL (operands[1]));
+      operands[1] = gen_int_mode (-INTVAL (operands[1]), SImode);
       if (!INT_14_BITS (operands[1]))
 	operands[1] = force_reg (SImode, operands[1]);
       emit_insn (gen_addsi3 (index, operands[0], operands[1]));
