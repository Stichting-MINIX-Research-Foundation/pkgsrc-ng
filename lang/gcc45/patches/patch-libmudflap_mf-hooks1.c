$NetBSD$

--- libmudflap/mf-hooks1.c.orig	Tue Sep  1 18:13:18 2009
+++ libmudflap/mf-hooks1.c
@@ -33,7 +33,7 @@ see the files COPYING3 and COPYING.RUNTIME respectivel
 
 /* These attempt to coax various unix flavours to declare all our
    needed tidbits in the system headers.  */
-#if !defined(__FreeBSD__)  && !defined(__APPLE__)
+#if !defined(__FreeBSD__)  && !defined(__APPLE__) && !defined(__NetBSD__)
 #define _POSIX_SOURCE
 #endif /* Some BSDs break <sys/socket.h> if this is defined. */
 #define _GNU_SOURCE
@@ -238,7 +238,7 @@ WRAPPER(void, free, void *buf)
   static int freeq_initialized = 0;
   DECLARE(void, free, void *);
 
-  BEGIN_PROTECT (free, buf);
+  BEGIN_PROTECTV (free, buf);
 
   if (UNLIKELY(buf == NULL))
     return;
