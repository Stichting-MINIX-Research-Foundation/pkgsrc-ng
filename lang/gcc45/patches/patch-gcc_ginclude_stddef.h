--- gcc/ginclude/stddef.h.orig   Tue Mar  8 13:03:34 2011
+++ gcc/ginclude/stddef.h
 
 /* On 4.3bsd-net2, make sure ansi.h is included, so we have
    one less case to deal with in the following.  */
-#if defined (__BSD_NET2__) || defined (____386BSD____) || (defined (__FreeBSD__) && (__FreeBSD__ < 5)) || defined(__NetBSD__)
+#if defined (__BSD_NET2__) || defined (____386BSD____) || (defined (__FreeBSD__) && (__FreeBSD__ < 5)) || defined(__NetBSD__) || defined(__minix)
+#ifndef inhibit_libc
 #include <machine/ansi.h>
+#endif
 #endif
 /* On FreeBSD 5, machine/ansi.h does not exist anymore... */
 #if defined (__FreeBSD__) && (__FreeBSD__ >= 5)
