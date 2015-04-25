$NetBSD$

--- gcc/testsuite/gcc.target/i386/avx-check.h.orig	Mon Feb  7 13:15:14 2011
+++ gcc/testsuite/gcc.target/i386/avx-check.h
@@ -1,6 +1,7 @@
 #include <stdlib.h>
 #include "cpuid.h"
 #include "m256-check.h"
+#include "avx-os-support.h"
 
 static void avx_test (void);
 
@@ -20,7 +21,8 @@ main ()
     return 0;
 
   /* Run AVX test only if host has AVX support.  */
-  if ((ecx & (bit_AVX | bit_OSXSAVE)) == (bit_AVX | bit_OSXSAVE))
+  if (((ecx & (bit_AVX | bit_OSXSAVE)) == (bit_AVX | bit_OSXSAVE))
+      && avx_os_support ())
     {
       do_test ();
 #ifdef DEBUG
