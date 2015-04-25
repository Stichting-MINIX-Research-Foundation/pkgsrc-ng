$NetBSD$

--- gcc/testsuite/g++.dg/torture/pr49615.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/torture/pr49615.C
@@ -0,0 +1,29 @@
+/* { dg-do compile } */
+/* { dg-options "-g" } */
+
+template <class T>
+static inline bool Dispatch (T* obj, void (T::*func) ())
+{
+  (obj->*func) ();
+}
+class C
+{
+  bool f (int);
+  void g ();
+};
+bool C::f (int n)
+{
+  bool b;
+  switch (n)
+    {
+      case 0:
+	  b = Dispatch (this, &C::g);
+      case 1:
+	  b = Dispatch (this, &C::g);
+    }
+}
+void C::g ()
+{
+  for (;;) { }
+}
+
