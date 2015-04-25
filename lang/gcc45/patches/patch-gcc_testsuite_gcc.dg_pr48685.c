$NetBSD$

--- gcc/testsuite/gcc.dg/pr48685.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/pr48685.c
@@ -0,0 +1,11 @@
+/* PR c/48685 */
+/* { dg-do compile } */
+/* { dg-options "-O2" } */
+
+int
+main ()
+{
+  int v = 1;
+  (void) (1 == 2 ? (void) 0 : (v = 0));
+  return v;
+}
