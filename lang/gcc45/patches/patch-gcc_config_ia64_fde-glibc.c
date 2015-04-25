$NetBSD$

--- gcc/config/ia64/fde-glibc.c.orig	Fri Aug 14 20:56:31 2009
+++ gcc/config/ia64/fde-glibc.c
@@ -34,9 +34,11 @@
 #include <link.h>
 #include "unwind-ia64.h"
 
+#if !defined(__NetBSD__)
 #if __GLIBC__ < 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ < 2) \
     || (__GLIBC__ == 2 && __GLIBC_MINOR__ == 2 && !defined(DT_CONFIG))
 # error You need GLIBC 2.2.4 or later on IA-64 Linux
+#endif
 #endif
 
 struct unw_ia64_callback_data
