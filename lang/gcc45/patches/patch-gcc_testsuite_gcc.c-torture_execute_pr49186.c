$NetBSD$

--- gcc/testsuite/gcc.c-torture/execute/pr49186.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.c-torture/execute/pr49186.c
@@ -0,0 +1,15 @@
+/* PR target/49186 */
+extern void abort (void);
+
+int
+main ()
+{
+  int x;
+  unsigned long long uv = 0x1000000001ULL;
+
+  x = (uv < 0x80) ? 1 : ((uv < 0x800) ? 2 : 3);
+  if (x != 3)
+    abort ();
+
+  return 0;
+}
