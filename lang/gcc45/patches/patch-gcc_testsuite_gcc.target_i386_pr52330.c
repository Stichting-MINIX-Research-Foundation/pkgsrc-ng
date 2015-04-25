$NetBSD$

--- gcc/testsuite/gcc.target/i386/pr52330.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.target/i386/pr52330.c
@@ -0,0 +1,7 @@
+/* { dg-do compile } */
+/* { dg-options "-O0" } */
+
+void foo (int a)
+{
+  asm volatile ("# %H0" : : "r" (a));  /* { dg-error "not an offsettable" } */
+}
