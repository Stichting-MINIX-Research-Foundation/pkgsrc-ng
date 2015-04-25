$NetBSD$

--- gcc/testsuite/gcc.c-torture/compile/pr48742.c.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/gcc.c-torture/compile/pr48742.c
@@ -0,0 +1,15 @@
+/* PR c/48742 */
+
+void baz (int);
+
+int
+foo (void)
+{
+  return 1 / 0 > 0;
+}
+
+void
+bar (void)
+{
+  baz (1 <= 2 % (3 >> 1 > 5 / 6 == 3));
+}
