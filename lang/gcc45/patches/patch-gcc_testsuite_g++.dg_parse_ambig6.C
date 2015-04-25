$NetBSD$

--- gcc/testsuite/g++.dg/parse/ambig6.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/parse/ambig6.C
@@ -0,0 +1,12 @@
+// PR c++/48046
+
+namespace N1 { typedef int   T; } // { dg-error "" }
+namespace N2 { typedef float T; } // { dg-error "" }
+
+int main()
+{
+  using namespace N1;
+  using namespace N2;
+
+  static T t;			// { dg-error "" }
+}
