$NetBSD$

--- gcc/testsuite/g++.dg/torture/pr51344.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/torture/pr51344.C
@@ -0,0 +1,11 @@
+/* { dg-do compile { target { i?86-*-* && ilp32 } } } */
+class A;
+
+template <class T>
+class B
+{
+  friend __attribute__((cdecl)) A& operator >>(A& a, B& b)
+  {
+    return a;
+  }
+};
