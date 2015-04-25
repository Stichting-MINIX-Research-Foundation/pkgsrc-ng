$NetBSD$

--- libstdc++-v3/libsupc++/eh_arm.cc.orig	Thu Apr  9 15:00:19 2009
+++ libstdc++-v3/libsupc++/eh_arm.cc
@@ -92,7 +92,12 @@ __cxa_type_match(_Unwind_Exception* ue_header,
 }
 
 // ABI defined routine called at the start of a cleanup handler.
-extern "C" bool
+extern "C"
+#ifdef __ARM_EABI_UNWINDER__
+void
+#else
+bool
+#endif
 __cxa_begin_cleanup(_Unwind_Exception* ue_header)
 {
   __cxa_eh_globals *globals = __cxa_get_globals();
@@ -121,7 +126,9 @@ __cxa_begin_cleanup(_Unwind_Exception* ue_header)
       globals->propagatingExceptions = header;
     }
 
+#ifndef __ARM_EABI_UNWINDER__
   return true;
+#endif
 }
 
 // Do the work for __cxa_end_cleanup.  Returns the currently propagating
