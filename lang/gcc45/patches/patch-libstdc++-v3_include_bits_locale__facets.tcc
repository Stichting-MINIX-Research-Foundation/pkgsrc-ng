$NetBSD$

--- libstdc++-v3/include/bits/locale_facets.tcc.orig	Sat Jul 18 22:58:10 2009
+++ libstdc++-v3/include/bits/locale_facets.tcc
@@ -464,7 +464,7 @@ _GLIBCXX_BEGIN_LDBL_NAMESPACE
 	bool __testfail = false;
 	bool __testoverflow = false;
 	const __unsigned_type __max =
-	  (__negative && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
+	  (__negative && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed_val)
 	  ? -__gnu_cxx::__numeric_traits<_ValueT>::__min
 	  : __gnu_cxx::__numeric_traits<_ValueT>::__max;
 	const __unsigned_type __smax = __max / __base;
@@ -568,7 +568,7 @@ _GLIBCXX_BEGIN_LDBL_NAMESPACE
 	else if (__testoverflow)
 	  {
 	    if (__negative
-		&& __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
+		&& __gnu_cxx::__numeric_traits<_ValueT>::__is_signed_val)
 	      __v = __gnu_cxx::__numeric_traits<_ValueT>::__min;
 	    else
 	      __v = __gnu_cxx::__numeric_traits<_ValueT>::__max;
@@ -891,7 +891,7 @@ _GLIBCXX_BEGIN_LDBL_NAMESPACE
 	    if (__v >= 0)
 	      {
 		if (bool(__flags & ios_base::showpos)
-		    && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed)
+		    && __gnu_cxx::__numeric_traits<_ValueT>::__is_signed_val)
 		  *--__cs = __lit[__num_base::_S_oplus], ++__len;
 	      }
 	    else
