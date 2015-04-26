$NetBSD$

--- include/elf/common.h.orig	Tue Sep  4 12:53:47 2012
+++ include/elf/common.h
@@ -607,6 +607,7 @@
 /* Values for NetBSD .note.netbsd.ident notes.  Note name is "NetBSD".  */
 
 #define NT_NETBSD_IDENT		1
+#define NT_NETBSD_MARCH		5
 
 /* Values for OpenBSD .note.openbsd.ident notes.  Note name is "OpenBSD".  */
 
