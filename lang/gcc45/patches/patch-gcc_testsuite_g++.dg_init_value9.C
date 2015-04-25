$NetBSD$

--- gcc/testsuite/g++.dg/init/value9.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/init/value9.C
@@ -0,0 +1,32 @@
+// PR c++/50793
+// { dg-do run }
+
+struct NonTrivial
+{
+  NonTrivial() { }
+};
+
+struct S
+{
+  NonTrivial nt;
+  int i;
+};
+
+int f(S s)
+{
+  s.i = 0xdeadbeef;
+  return s.i;
+}
+
+int g(S s = S())
+{
+  return s.i;
+}
+
+int main()
+{
+  f(S());  // make stack dirty
+
+  if ( g() )
+    __builtin_abort();
+}
