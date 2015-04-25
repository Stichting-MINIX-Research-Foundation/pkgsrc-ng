$NetBSD$

--- gcc/testsuite/g++.dg/cpp0x/rv-cast4.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/cpp0x/rv-cast4.C
@@ -0,0 +1,13 @@
+// PR c++/51161
+// { dg-options "-std=c++0x" }
+
+struct A{};
+struct B : A{};
+struct C : A{};
+struct D : B, C{};
+
+int main()
+{
+  D d;
+  static_cast<A &&>(d);		// { dg-error "ambiguous" }
+}
