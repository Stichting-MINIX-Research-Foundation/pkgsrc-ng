$NetBSD$

--- gcc/config/mips/mips.md.orig	Fri Apr  2 19:54:46 2010
+++ gcc/config/mips/mips.md
@@ -4806,7 +4806,7 @@
 ;; of _gp from the start of this function.  Operand 1 is the incoming
 ;; function address.
 (define_insn_and_split "loadgp_newabi_<mode>"
-  [(set (match_operand:P 0 "register_operand" "=d")
+  [(set (match_operand:P 0 "register_operand" "=&d")
 	(unspec:P [(match_operand:P 1)
 		   (match_operand:P 2 "register_operand" "d")]
 		  UNSPEC_LOADGP))]
