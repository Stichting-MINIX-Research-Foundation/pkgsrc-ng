$NetBSD$

--- gcc/testsuite/gcc.target/mips/reg-var-1.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.target/mips/reg-var-1.c
@@ -0,0 +1,16 @@
+/* { dg-do run } */
+register int g asm ("$18");
+
+void __attribute__((noinline))
+test (void)
+{
+  g = g + 1;
+}
+
+int
+main (void)
+{
+  g = 2;
+  test ();
+  return g != 3;
+}
