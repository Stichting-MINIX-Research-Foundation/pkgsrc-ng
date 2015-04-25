$NetBSD$

--- libstdc++-v3/include/ext/numeric_traits.h.orig	Thu Apr  9 15:00:19 2009
+++ libstdc++-v3/include/ext/numeric_traits.h
@@ -58,7 +58,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
 
       // NB: these two also available in std::numeric_limits as compile
       // time constants, but <limits> is big and we avoid including it.
-      static const bool __is_signed = __glibcxx_signed(_Value);
+      static const bool __is_signed_val = __glibcxx_signed(_Value);
       static const int __digits = __glibcxx_digits(_Value);      
     };
 
@@ -69,7 +69,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
     const _Value __numeric_traits_integer<_Value>::__max;
 
   template<typename _Value>
-    const bool __numeric_traits_integer<_Value>::__is_signed;
+    const bool __numeric_traits_integer<_Value>::__is_signed_val;
 
   template<typename _Value>
     const int __numeric_traits_integer<_Value>::__digits;
@@ -101,7 +101,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
       static const int __max_digits10 = __glibcxx_max_digits10(_Value);
 
       // See above comment...
-      static const bool __is_signed = true;
+      static const bool __is_signed_val = true;
       static const int __digits10 = __glibcxx_digits10(_Value);
       static const int __max_exponent10 = __glibcxx_max_exponent10(_Value);
     };
@@ -110,7 +110,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
     const int __numeric_traits_floating<_Value>::__max_digits10;
 
   template<typename _Value>
-    const bool __numeric_traits_floating<_Value>::__is_signed;
+    const bool __numeric_traits_floating<_Value>::__is_signed_val;
 
   template<typename _Value>
     const int __numeric_traits_floating<_Value>::__digits10;
