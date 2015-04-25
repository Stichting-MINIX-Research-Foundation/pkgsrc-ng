$NetBSD$

--- gcc/testsuite/gcc.target/sparc/cas64.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.target/sparc/cas64.c
@@ -0,0 +1,15 @@
+/* PR target/49660 */
+
+/* { dg-do compile { target sparc*-*-solaris2.* } } */
+
+#include <stdint.h>
+
+extern int64_t *val, old, new;
+
+int
+cas64 (void)
+{
+  return __sync_bool_compare_and_swap (val, old, new);
+}
+
+/* { dg-final { scan-assembler-not "compare_and_swap_8" } } */
