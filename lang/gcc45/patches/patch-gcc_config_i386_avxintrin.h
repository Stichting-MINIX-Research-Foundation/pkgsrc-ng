$NetBSD$

--- gcc/config/i386/avxintrin.h.orig	Mon Feb 21 20:02:02 2011
+++ gcc/config/i386/avxintrin.h
@@ -759,7 +759,7 @@ _mm256_insert_epi8 (__m256i __X, int __D, int const __
 
 #ifdef __x86_64__
 extern __inline __m256i __attribute__((__gnu_inline__, __always_inline__, __artificial__))
-_mm256_insert_epi64 (__m256i __X, int __D, int const __N)
+_mm256_insert_epi64 (__m256i __X, long long __D, int const __N)
 {
   __m128i __Y = _mm256_extractf128_si256 (__X, __N >> 1);
   __Y = _mm_insert_epi64 (__Y, __D, __N % 2);
