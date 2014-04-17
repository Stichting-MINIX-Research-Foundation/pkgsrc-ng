$NetBSD$

--- ncurses/tinfo/lib_baudrate.c.orig	Sun Dec 19 01:50:50 2010
+++ ncurses/tinfo/lib_baudrate.c
@@ -49,7 +49,7 @@
  * of the indices up to B115200 fit nicely in a 'short', allowing us to retain
  * ospeed's type for compatibility.
  */
-#if (defined(__FreeBSD__) && (__FreeBSD_version < 700000)) || defined(__NetBSD__) || defined(__OpenBSD__)
+#if (defined(__FreeBSD__) && (__FreeBSD_version < 700000)) || defined(__minix) || defined(__NetBSD__) || defined(__OpenBSD__)
 #undef B0
 #undef B50
 #undef B75
