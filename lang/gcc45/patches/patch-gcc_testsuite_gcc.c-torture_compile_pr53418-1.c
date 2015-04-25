$NetBSD$

--- gcc/testsuite/gcc.c-torture/compile/pr53418-1.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.c-torture/compile/pr53418-1.c
@@ -0,0 +1,5 @@
+void
+f (void)
+{
+  int i = (0 ? 1 : 0U / 0);
+}
