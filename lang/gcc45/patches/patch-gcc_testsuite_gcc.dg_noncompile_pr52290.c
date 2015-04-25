$NetBSD$

--- gcc/testsuite/gcc.dg/noncompile/pr52290.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/noncompile/pr52290.c
@@ -0,0 +1,3 @@
+/* { dg-error "undeclared here" "" { target *-*-* } 3 } */
+/* { dg-error "expected" "" { target *-*-* } 3 } */
+int f()[j]
