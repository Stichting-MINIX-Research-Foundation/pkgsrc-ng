$NetBSD$

--- gcc/testsuite/gcc.target/i386/aes-avx-check.h.orig	Mon Jun  7 11:08:46 2010
+++ gcc/testsuite/gcc.target/i386/aes-avx-check.h
@@ -3,6 +3,7 @@
 #endif
 #include <stdlib.h>
 #include "cpuid.h"
+#include "avx-os-support.h"
 
 static void aes_avx_test (void);
 
@@ -22,7 +23,9 @@ main ()
     return 0;
 
   /* Run AES + AVX test only if host has AES + AVX support.  */
-  if ((ecx & (bit_AVX | bit_AES)) == (bit_AVX | bit_AES))
+  if (((ecx & (bit_AVX | bit_OSXSAVE | bit_AES))
+       == (bit_AVX | bit_OSXSAVE | bit_AES))
+      && avx_os_support ())
     {
       do_test ();
 #ifdef DEBUG
