$NetBSD$

--- gcc/crtstuff.c.orig	Wed Nov 25 10:55:54 2009
+++ gcc/crtstuff.c
@@ -92,6 +92,15 @@ call_ ## FUNC (void)					\
     && !defined(OBJECT_FORMAT_FLAT) \
     && defined(HAVE_LD_EH_FRAME_HDR) \
     && !defined(inhibit_libc) && !defined(CRTSTUFFT_O) \
+    && defined(__NetBSD__)
+#include <link.h>
+# define USE_PT_GNU_EH_FRAME
+#endif
+
+#if defined(OBJECT_FORMAT_ELF) \
+    && !defined(OBJECT_FORMAT_FLAT) \
+    && defined(HAVE_LD_EH_FRAME_HDR) \
+    && !defined(inhibit_libc) && !defined(CRTSTUFFT_O) \
     && defined(__GLIBC__) && __GLIBC__ >= 2
 #include <link.h>
 /* uClibc pretends to be glibc 2.2 and DT_CONFIG is defined in its link.h.
