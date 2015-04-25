$NetBSD$

--- gcc/testsuite/gcc.target/i386/sse2-init-v2di-2.c.orig	Wed Aug 20 13:22:30 2008
+++ gcc/testsuite/gcc.target/i386/sse2-init-v2di-2.c
@@ -1,6 +1,6 @@
 /* { dg-do compile } */
 /* { dg-require-effective-target lp64 } */
-/* { dg-options "-O2 -msse4 -march=core2" } */
+/* { dg-options "-O2 -msse4 -march=core2 -dp" } */
 
 #include <emmintrin.h>
 
@@ -10,4 +10,4 @@ test (long long b)
   return _mm_cvtsi64_si128 (b); 
 }
 
-/* { dg-final { scan-assembler "movq" } } */
+/* { dg-final { scan-assembler-times "\\*vec_concatv2di_rex64_sse4_1/3" 1 } } */
