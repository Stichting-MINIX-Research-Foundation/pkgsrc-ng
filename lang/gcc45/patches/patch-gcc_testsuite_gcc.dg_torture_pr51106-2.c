$NetBSD$

--- gcc/testsuite/gcc.dg/torture/pr51106-2.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/torture/pr51106-2.c
@@ -0,0 +1,14 @@
+/* PR target/51106 */
+/* { dg-do "compile" } */
+/* { dg-skip-if "RTL error" { "*-*-*" } { "-fno-fat-lto-objects" } { "" } } */
+
+int
+bar (int x)
+{
+  asm goto ("" : : "i" (x) : : lab); /* { dg-error "impossible constraint" } */
+  __builtin_unreachable ();
+lab:
+  return 0;
+}
+
+/* { dg-warning "probably doesn.t match constraints" "" { target *-*-* } 8 } */
