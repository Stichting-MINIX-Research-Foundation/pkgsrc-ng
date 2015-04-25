$NetBSD$

--- gcc/testsuite/gcc.dg/dfp/pr52140.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.dg/dfp/pr52140.c
@@ -0,0 +1,10 @@
+/* { dg-do compile } */
+/* { dg-options "-O1" } */
+
+/* This used to result in an ICE.  */
+
+int
+foo (_Decimal64 x, _Decimal64 y)
+{
+  return (x < y) || (x > y);
+}
