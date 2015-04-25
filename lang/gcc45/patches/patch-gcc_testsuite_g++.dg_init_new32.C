$NetBSD$

--- gcc/testsuite/g++.dg/init/new32.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/init/new32.C
@@ -0,0 +1,16 @@
+// PR c++/48873
+
+#include <new>
+
+struct D {
+private:
+  ~D();
+};
+
+template<class T>
+T& create();
+
+void f()
+{
+  D* dp = new (((void*) 0)) D(create<D>()); // #
+}
