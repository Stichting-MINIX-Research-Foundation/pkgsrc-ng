$NetBSD$

--- gcc/testsuite/gcc.c-torture/compile/pr49238.c.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/gcc.c-torture/compile/pr49238.c
@@ -0,0 +1,18 @@
+/* PR target/49238 */
+extern int bar (void);
+
+void
+foo (unsigned long long a, int b)
+{
+  int i;
+
+  if (b)
+    for (a = -12; a >= 10; a = bar ())
+      break;
+  else
+    return;
+
+  for (i = 0; i < 10; i += 10)
+    if ((i == bar ()) | (bar () >= a))
+      bar ();
+}
