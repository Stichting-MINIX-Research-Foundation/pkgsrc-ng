$NetBSD$

--- gcc/testsuite/gcc.dg/pr51408.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/pr51408.c
@@ -0,0 +1,22 @@
+/* This testcase used to fail because of a bug in 
+   arm.md:*minmax_arithsi.  */
+
+/* { dg-do run } */
+/* { dg-options "-O1" } */
+
+extern void abort (void);
+
+int __attribute__((noinline))
+foo (int a, int b)
+{
+  int max = (b > 0) ? b : 0;
+  return max - a;
+}
+
+int
+main (void)
+{
+  if (foo (3, -1) != -3)
+    abort ();
+  return 0;
+}
