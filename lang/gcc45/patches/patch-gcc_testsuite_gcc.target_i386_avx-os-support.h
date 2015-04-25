$NetBSD$

--- gcc/testsuite/gcc.target/i386/avx-os-support.h.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.target/i386/avx-os-support.h
@@ -0,0 +1,10 @@
+/* Check if the OS supports executing AVX instructions.  */
+
+static int
+avx_os_support (void)
+{
+  unsigned int eax, edx;
+
+  __asm__ ("xgetbv" : "=a" (eax), "=d" (edx) : "c" (0));
+  return (eax & 6) == 6;
+}
