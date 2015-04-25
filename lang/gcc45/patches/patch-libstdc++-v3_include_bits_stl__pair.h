$NetBSD$

--- libstdc++-v3/include/bits/stl_pair.h.orig	Thu Jun 10 10:26:14 2010
+++ libstdc++-v3/include/bits/stl_pair.h
@@ -107,6 +107,9 @@ _GLIBCXX_BEGIN_NAMESPACE(std)
         pair(_U1&& __x, _U2&& __y)
 	: first(std::forward<_U1>(__x)),
 	  second(std::forward<_U2>(__y)) { }
+
+      pair(const pair &) = default;
+      pair(pair &&) = default;
 #endif
 
       /** There is also a templated copy ctor for the @c pair class itself.  */
@@ -120,6 +123,14 @@ _GLIBCXX_BEGIN_NAMESPACE(std)
         pair(pair<_U1, _U2>&& __p)
 	: first(std::forward<_U1>(__p.first)),
 	  second(std::forward<_U2>(__p.second)) { }
+
+      pair&
+      operator=(const pair& __p)
+      { 
+	first = __p.first;
+	second = __p.second;
+	return *this;
+      }
 
       pair&
       operator=(pair&& __p)
