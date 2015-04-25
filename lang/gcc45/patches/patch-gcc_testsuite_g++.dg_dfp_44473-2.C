$NetBSD$

--- gcc/testsuite/g++.dg/dfp/44473-2.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/dfp/44473-2.C
@@ -0,0 +1,25 @@
+// { dg-do compile }
+
+// Mangling of classes from std::decimal are special-cased.
+
+namespace std {
+  namespace decimal {
+    class decimal64 {
+      public:
+	typedef float __decfloat64 __attribute__ ((mode (DD)));
+	explicit decimal64 (int __r):__val (__r) {}
+      private:
+	__decfloat64 __val;
+    };
+  }
+}
+
+int bar (const std::decimal::decimal64 & x) { }
+
+int foo ()
+{
+  std::decimal::decimal64 x(0);
+  bar (x);
+}
+
+// { dg-final { scan-assembler "_Z3barRKDd:" } }
