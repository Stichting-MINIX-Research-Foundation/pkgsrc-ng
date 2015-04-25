$NetBSD$

--- libstdc++-v3/libsupc++/nested_exception.h.orig	Thu Feb 18 17:20:16 2010
+++ libstdc++-v3/libsupc++/nested_exception.h
@@ -119,7 +119,7 @@ namespace std
   // with a type that has an accessible nested_exception base.
   template<typename _Ex>
     inline void
-    __throw_with_nested(_Ex&& __ex, const nested_exception* = 0)
+    __throw_with_nested(_Ex&& __ex, const nested_exception*)
     { throw __ex; }
 
   template<typename _Ex>
