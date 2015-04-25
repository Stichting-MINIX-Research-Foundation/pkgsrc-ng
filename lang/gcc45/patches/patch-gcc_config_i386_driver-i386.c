$NetBSD$

--- gcc/config/i386/driver-i386.c.orig	Sun May  9 14:53:00 2010
+++ gcc/config/i386/driver-i386.c
@@ -436,7 +436,8 @@ const char *host_detect_local_cpu (int argc, const cha
   has_ssse3 = ecx & bit_SSSE3;
   has_sse4_1 = ecx & bit_SSE4_1;
   has_sse4_2 = ecx & bit_SSE4_2;
-  has_avx = ecx & bit_AVX;
+  /* Don't check XCR0[2] - I think that can be 'lazy enabled' by the OS */
+  has_avx = (ecx & bit_AVX) && (ecx & bit_OSXSAVE);
   has_cmpxchg16b = ecx & bit_CMPXCHG16B;
   has_movbe = ecx & bit_MOVBE;
   has_popcnt = ecx & bit_POPCNT;
@@ -494,7 +495,7 @@ const char *host_detect_local_cpu (int argc, const cha
 	processor = PROCESSOR_AMDFAM10;
       else if (has_sse2 || has_longmode)
 	processor = PROCESSOR_K8;
-      else if (has_3dnowp)
+      else if (has_3dnowp && family == 6)
 	processor = PROCESSOR_ATHLON;
       else if (has_mmx)
 	processor = PROCESSOR_K6;
