$NetBSD$

--- libstdc++-v3/include/bits/stl_algobase.h.orig	Tue Mar 23 14:32:35 2010
+++ libstdc++-v3/include/bits/stl_algobase.h
@@ -929,8 +929,8 @@ _GLIBCXX_BEGIN_NAMESPACE(std)
       typedef typename iterator_traits<_II2>::value_type _ValueType2;
       const bool __simple =
 	(__is_byte<_ValueType1>::__value && __is_byte<_ValueType2>::__value
-	 && !__gnu_cxx::__numeric_traits<_ValueType1>::__is_signed
-	 && !__gnu_cxx::__numeric_traits<_ValueType2>::__is_signed
+	 && !__gnu_cxx::__numeric_traits<_ValueType1>::__is_signed_val
+	 && !__gnu_cxx::__numeric_traits<_ValueType2>::__is_signed_val
 	 && __is_pointer<_II1>::__value
 	 && __is_pointer<_II2>::__value);
 
