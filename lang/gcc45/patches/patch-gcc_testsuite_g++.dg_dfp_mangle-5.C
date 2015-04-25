$NetBSD$

--- gcc/testsuite/g++.dg/dfp/mangle-5.C.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/g++.dg/dfp/mangle-5.C
@@ -0,0 +1,29 @@
+// { dg-do compile }
+
+// Mangling of classes from std::decimal are special-cased.
+// Derived from g++.dg/abi/mangle35.C.
+
+namespace std {
+  namespace decimal {
+    class decimal128 {
+      public:
+	typedef float __decfloat128 __attribute__ ((mode (TD)));
+	explicit decimal128 (int __r):__val (__r) {}
+      private:
+	__decfloat128 __val;
+    };
+  }
+}
+
+template<void (*)()> struct A {};
+
+template<typename> void foo();
+
+template<typename T> A<foo<T> > bar();
+
+void baz()
+{
+  bar<std::decimal::decimal128>();
+}
+
+// { dg-final { scan-assembler "_Z3barIDeE1AIX3fooIT_EEEv" } }
