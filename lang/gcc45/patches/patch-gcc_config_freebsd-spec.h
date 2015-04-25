$NetBSD$

--- gcc/config/freebsd-spec.h.orig	Fri Feb 25 23:15:48 2011
+++ gcc/config/freebsd-spec.h
@@ -153,7 +153,7 @@ is built with the --enable-threads configure-time opti
 #define FBSD_DYNAMIC_LINKER "/libexec/ld-elf.so.1"
 #endif
 
-#if defined(HAVE_LD_EH_FRAME_HDR)
+#if defined(HAVE_LD_EH_FRAME_HDR) && !defined(LINK_EH_SPEC)
 #define LINK_EH_SPEC "%{!static:--eh-frame-hdr} "
 #endif
 
