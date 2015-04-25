$NetBSD$

--- gcc/config/m68k/constraints.md.orig	Mon May 18 07:54:44 2009
+++ gcc/config/m68k/constraints.md
@@ -94,7 +94,8 @@
 (define_constraint "T"
   "Used for operands that satisfy 's' when -mpcrel is not in effect."
   (and (match_code "symbol_ref,label_ref,const")
-       (match_test "!flag_pic")))
+       (match_test "!TARGET_PCREL")
+       (match_test "!flag_pic || LEGITIMATE_PIC_OPERAND_P (op)")))
 
 (define_memory_constraint "Q"
   "Means address register indirect addressing mode."
