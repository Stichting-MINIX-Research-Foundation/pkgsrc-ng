$NetBSD$

--- gcc/testsuite/gcc.c-torture/execute/doloop-1.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.c-torture/execute/doloop-1.c
@@ -0,0 +1,18 @@
+#include <limits.h>
+
+extern void exit (int);
+extern void abort (void);
+
+volatile unsigned int i;
+
+int
+main (void)
+{
+  unsigned char z = 0;
+
+  do ++i;
+  while (--z > 0);
+  if (i != UCHAR_MAX + 1U)
+    abort ();
+  exit (0);
+}
