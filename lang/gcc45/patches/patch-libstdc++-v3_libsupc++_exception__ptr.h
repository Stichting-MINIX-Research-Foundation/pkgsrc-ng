$NetBSD$

--- libstdc++-v3/libsupc++/exception_ptr.h.orig	Mon Nov  9 22:09:30 2009
+++ libstdc++-v3/libsupc++/exception_ptr.h
@@ -129,7 +129,7 @@ namespace std 
       operator==(const exception_ptr&, const exception_ptr&) throw() 
       __attribute__ ((__pure__));
 
-      const type_info*
+      const class type_info*
       __cxa_exception_type() const throw() __attribute__ ((__pure__));
     };
 
