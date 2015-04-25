$NetBSD$

--- gcc/testsuite/gcc.dg/pr49120.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/pr49120.c
@@ -0,0 +1,11 @@
+/* PR c/49120 */
+/* { dg-do compile } */
+/* { dg-options "-Wall" } */
+
+int
+main ()
+{
+  int a = 1;
+  int c = ({ char b[a + 1]; b[0] = 0; b[0]; });
+  return c;
+}
