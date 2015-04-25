$NetBSD$

--- gcc/testsuite/gcc.c-torture/execute/20120111-1.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.c-torture/execute/20120111-1.c
@@ -0,0 +1,18 @@
+#include <stdlib.h>
+#include <stdint.h>
+
+uint32_t f0a (uint64_t arg2) __attribute__((noinline));
+
+uint32_t
+f0a (uint64_t arg)
+{
+  return ~(arg > -3);
+}
+
+int main() {
+  uint32_t r1;
+  r1 = f0a (12094370573988097329ULL);
+  if (r1 != ~0U)
+    abort ();
+  return 0;
+}
