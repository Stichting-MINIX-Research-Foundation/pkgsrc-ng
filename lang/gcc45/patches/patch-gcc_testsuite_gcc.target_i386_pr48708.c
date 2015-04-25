$NetBSD$

--- gcc/testsuite/gcc.target/i386/pr48708.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.target/i386/pr48708.c
@@ -0,0 +1,15 @@
+/* { dg-do compile } */
+/* { dg-options "-O2 -msse2" } */
+
+#include <emmintrin.h>
+
+typedef long long T __attribute__((may_alias));
+struct S { __m128i d; };
+
+__m128i
+foo (long long *x, struct S *y, __m128i *z)
+{
+  struct S s = *y;
+  ((T *) &s.d)[0] = *x;
+  return _mm_cmpeq_epi16 (s.d, *z);
+}
