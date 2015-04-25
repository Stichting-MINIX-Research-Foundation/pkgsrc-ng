$NetBSD$

--- gcc/testsuite/gcc.c-torture/execute/pr48973-2.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.c-torture/execute/pr48973-2.c
@@ -0,0 +1,14 @@
+/* PR middle-end/48973 */
+
+extern void abort (void);
+struct S { int f : 1; } s;
+int v = -1;
+
+int
+main ()
+{
+  s.f = v < 0;
+  if ((unsigned int) s.f != -1U)
+    abort ();
+  return 0;
+}
