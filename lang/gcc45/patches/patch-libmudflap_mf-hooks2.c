$NetBSD$

--- libmudflap/mf-hooks2.c.orig	Thu Apr  9 15:00:19 2009
+++ libmudflap/mf-hooks2.c
@@ -32,9 +32,10 @@ see the files COPYING3 and COPYING.RUNTIME respectivel
 
 /* These attempt to coax various unix flavours to declare all our
    needed tidbits in the system headers.  */
-#if !defined(__FreeBSD__) && !defined(__APPLE__)
+#if !defined(__FreeBSD__) && !defined(__APPLE__) && !defined(__NetBSD__)
 #define _POSIX_SOURCE
 #endif /* Some BSDs break <sys/socket.h> if this is defined. */
+#define _NETBSD_SOURCE
 #define _GNU_SOURCE
 #define _XOPEN_SOURCE
 #define _BSD_TYPES
