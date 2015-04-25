$NetBSD$

--- gcc/testsuite/gcc.dg/torture/pr48542.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/torture/pr48542.c
@@ -0,0 +1,57 @@
+/* { dg-do run } */
+/* The return-address was clobbered.  */
+#include <stdlib.h>
+#include <setjmp.h>
+
+jmp_buf env;
+extern void sub(void);
+extern void sub3(void);
+int called;
+__attribute__ ((__noinline__))
+int sjtest()
+{
+  int i;
+  if (setjmp(env))
+    return 99;
+
+  for (i = 0; i < 10; i++)
+    sub();
+
+  longjmp(env, 1);
+}
+
+__attribute__ ((__noinline__))
+void sub(void)
+{
+  called++;
+}
+
+int called3;
+__attribute__ ((__noinline__))
+int sjtest3()
+{
+  int i;
+  if (setjmp(env))
+    return 42;
+
+  for (i = 0; i < 10; i++)
+    sub3();
+  return 0;
+}
+
+__attribute__ ((__noinline__))
+void sub3(void)
+{
+  called3++;
+  if (called3 == 10)
+    longjmp (env, 1);
+}
+
+int main(void)
+{
+  if (sjtest() != 99 || called != 10)
+    abort();
+  if (sjtest3() != 42 || called3 != 10)
+    abort();
+  exit (0);
+}
