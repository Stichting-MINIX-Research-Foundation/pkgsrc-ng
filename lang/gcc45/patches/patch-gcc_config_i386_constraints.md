$NetBSD$

--- gcc/config/i386/constraints.md.orig	Wed Jul  8 16:41:23 2009
+++ gcc/config/i386/constraints.md
@@ -149,7 +149,7 @@
 (define_constraint "G"
   "Standard 80387 floating point constant."
   (and (match_code "const_double")
-       (match_test "standard_80387_constant_p (op)")))
+       (match_test "standard_80387_constant_p (op) > 0")))
 
 ;; This can theoretically be any mode's CONST0_RTX.
 (define_constraint "C"
