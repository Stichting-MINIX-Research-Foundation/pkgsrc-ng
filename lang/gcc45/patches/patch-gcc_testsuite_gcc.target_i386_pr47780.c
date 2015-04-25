$NetBSD$

--- gcc/testsuite/gcc.target/i386/pr47780.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.target/i386/pr47780.c
@@ -0,0 +1,14 @@
+/* PR debug/47780 */
+/* { dg-do compile } */
+/* { dg-options "-O -fgcse -fgcse-las -fstack-protector-all -fno-tree-ccp -fno-tree-dominator-opts -fcompare-debug -Wno-psabi" } */
+
+typedef int V2SF __attribute__ ((vector_size (128)));
+
+V2SF
+foo (int x, V2SF a)
+{
+  V2SF b = a + (V2SF) {};
+  while (x--)
+    a += b;
+  return a;
+}
