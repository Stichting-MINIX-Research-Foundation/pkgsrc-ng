$NetBSD$

--- gcc/testsuite/g++.dg/template/nontype23.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/template/nontype23.C
@@ -0,0 +1,9 @@
+// PR c++/48936
+
+template <bool C> int foo (void);
+template <class T> struct S
+{
+  static const unsigned int a = sizeof (T);
+  enum { c = sizeof (foo <(a == 0)> ()) };
+};
+S<int> x;
