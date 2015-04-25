$NetBSD$

--- libstdc++-v3/libsupc++/unwind-cxx.h.orig	Sun May  3 16:51:50 2009
+++ libstdc++-v3/libsupc++/unwind-cxx.h
@@ -196,8 +196,8 @@ typedef enum {
   ctm_succeeded = 1,
   ctm_succeeded_with_ptr_to_base = 2
 } __cxa_type_match_result;
-extern "C" bool __cxa_type_match(_Unwind_Exception*, const std::type_info*,
-				 bool, void**);
+extern "C" __cxa_type_match_result __cxa_type_match(_Unwind_Exception*,
+    const std::type_info*, bool, void**);
 extern "C" void __cxa_begin_cleanup (_Unwind_Exception*);
 extern "C" void __cxa_end_cleanup (void);
 #endif
