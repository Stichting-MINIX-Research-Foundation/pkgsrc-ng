$NetBSD$

--- gcc/testsuite/gcc.c-torture/compile/pr50565-1.c.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/gcc.c-torture/compile/pr50565-1.c
@@ -0,0 +1,4 @@
+struct s { char p[2]; };
+static struct s v;
+const int o0 = (int) ((void *) &v.p[0] - (void *) &v) + 0U;
+const int o1 = (int) ((void *) &v.p[0] - (void *) &v) + 1U;
