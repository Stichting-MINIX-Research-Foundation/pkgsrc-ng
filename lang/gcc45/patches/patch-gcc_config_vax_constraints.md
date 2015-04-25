$NetBSD$

--- gcc/config/vax/constraints.md.orig	Wed Apr  1 17:00:00 2009
+++ gcc/config/vax/constraints.md
@@ -113,5 +113,6 @@
 
 (define_constraint "T"
     "@internal satisfies CONSTANT_P and, if pic is enabled, is not a SYMBOL_REF, LABEL_REF, or CONST."
-   (ior (not (match_code "const,symbol_ref,label_ref"))
-	(match_test "!flag_pic")))
+   (and (match_test "CONSTANT_P (op)")
+	(ior (not (match_code "const,symbol_ref,label_ref"))
+	     (match_test "!flag_pic"))))
