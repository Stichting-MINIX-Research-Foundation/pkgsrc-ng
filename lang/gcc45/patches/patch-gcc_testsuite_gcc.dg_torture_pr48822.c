$NetBSD$

--- gcc/testsuite/gcc.dg/torture/pr48822.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/torture/pr48822.c
@@ -0,0 +1,20 @@
+/* { dg-do compile } */
+
+void foo (int *, int *);
+int bar ()
+{
+  int a = 0;
+  int b = 0;
+  if (b != 0)
+    {
+      int ax = a;
+      int bx = b;
+      while (bx != 0)
+	{
+	  int tem = ax % bx;
+	  ax = bx;
+	  bx = tem;
+	}
+    }
+  foo (&a, &b);
+}
