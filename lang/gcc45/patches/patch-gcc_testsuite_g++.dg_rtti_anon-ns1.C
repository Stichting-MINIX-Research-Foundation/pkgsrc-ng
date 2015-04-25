$NetBSD$

--- gcc/testsuite/g++.dg/rtti/anon-ns1.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/rtti/anon-ns1.C
@@ -0,0 +1,15 @@
+// PR c++/49440
+// The typeinfo name for A should start with * so we compare
+// it by address rather than contents.
+
+// { dg-final { scan-assembler "\"\*N\[^\"\]+1AE" } }
+
+namespace
+{
+  class A { };
+}
+
+void f()
+{
+  throw A();
+}
