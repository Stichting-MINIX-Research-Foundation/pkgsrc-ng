$NetBSD$

--- libmudflap/mf-runtime.h.orig	Thu Apr  9 15:00:19 2009
+++ libmudflap/mf-runtime.h
@@ -31,7 +31,7 @@ see the files COPYING3 and COPYING.RUNTIME respectivel
 #define MF_RUNTIME_H
 
 typedef void *__mf_ptr_t;
-typedef unsigned int __mf_uintptr_t __attribute__ ((__mode__ (__pointer__)));
+typedef unsigned long __mf_uintptr_t __attribute__ ((__mode__ (__pointer__)));
 typedef __SIZE_TYPE__ __mf_size_t;
 
 /* Global declarations used by instrumentation.  When _MUDFLAP is
@@ -81,11 +81,11 @@ extern "C" {
 #endif
 
 extern void __mf_check (void *ptr, __mf_size_t sz, int type, const char *location)
-       __attribute((nothrow));
+       __attribute__((nothrow));
 extern void __mf_register (void *ptr, __mf_size_t sz, int type, const char *name)
-       __attribute((nothrow));
+       __attribute__((nothrow));
 extern void __mf_unregister (void *ptr, __mf_size_t sz, int type)
-       __attribute((nothrow));
+       __attribute__((nothrow));
 extern unsigned __mf_watch (void *ptr, __mf_size_t sz);
 extern unsigned __mf_unwatch (void *ptr, __mf_size_t sz);
 extern void __mf_report ();
