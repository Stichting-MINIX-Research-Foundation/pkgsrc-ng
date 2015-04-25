$NetBSD$

--- gcc/testsuite/gcc.dg/ipa/pr45644.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/ipa/pr45644.c
@@ -0,0 +1,35 @@
+/* Verify that we do not IPA-SRA bitfields.  */
+/* { dg-do run } */
+/* { dg-options "-O2"  } */
+
+extern void abort (void);
+
+struct S
+{
+  int j : 8;
+  int i : 24;
+  int l;
+};
+
+static int __attribute__((noinline)) foo (struct S *s)
+{
+  int z = s->i;
+  if (z != 777)
+    abort ();
+  return 0;
+}
+
+int __attribute__((noinline)) bar (struct S *s)
+{
+  return foo (s);
+}
+
+int main (int argc, char *argv[])
+{
+  struct S s;
+  s.j = 5;
+  s.i = 777;
+  s.l = -1;
+
+  return bar (&s);
+}
