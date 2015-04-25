$NetBSD$

--- gcc/testsuite/gcc.target/arm/pr51835.c.orig	Wed May 21 19:48:58 2014
+++ gcc/testsuite/gcc.target/arm/pr51835.c
@@ -0,0 +1,14 @@
+/* { dg-do compile } */
+/* { dg-options "-O2 -mfloat-abi=hard -mfpu=fpv4-sp-d16" }  */
+/* { dg-require-effective-target arm_thumb2_ok } */
+
+int func1 (double d)
+{
+  return (int)d;
+}
+unsigned int func2 (double d)
+{
+  return (unsigned int)d;
+}
+
+/* { dg-final { scan-assembler-times "fmrrd\[\\t \]+r0,\[\\t \]*r1,\[\\t \]*d0" 2 } } */
