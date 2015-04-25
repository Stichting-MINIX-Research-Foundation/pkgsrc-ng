$NetBSD$

--- gcc/testsuite/g++.dg/init/new30.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/init/new30.C
@@ -0,0 +1,15 @@
+// PR c++/40975
+
+struct data_type
+{
+    // constructor required to reproduce compiler bug
+    data_type() {}
+};
+
+struct ptr_type
+{
+    // array new as default argument required to reproduce compiler bug
+    ptr_type (data_type* ptr = new data_type[1]) { delete[] ptr; }
+};
+
+ptr_type obj;
