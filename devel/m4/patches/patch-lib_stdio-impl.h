--- lib/stdio-impl.h.orig	Sun Sep 22 06:20:02 2013
+++ lib/stdio-impl.h	Fri Apr 18 00:02:53 2014
@@ -21,7 +21,7 @@
 
 /* BSD stdio derived implementations.  */
 
-#if defined __NetBSD__                         /* NetBSD */
+#if defined __NetBSD__ || defined __minix                        /* NetBSD */
 /* Get __NetBSD_Version__.  */
 # include <sys/param.h>
 #endif
@@ -57,7 +57,7 @@
 #  define fp_ fp
 # endif
 
-# if (defined __NetBSD__ && __NetBSD_Version__ >= 105270000) || defined __OpenBSD__ || defined __ANDROID__ /* NetBSD >= 1.5ZA, OpenBSD, Android */
+# if (defined __NetBSD__ && __NetBSD_Version__ >= 105270000) || defined __OpenBSD__ || defined __ANDROID__  || defined __minix /* NetBSD >= 1.5ZA, OpenBSD, Android */
   /* See <http://cvsweb.netbsd.org/bsdweb.cgi/src/lib/libc/stdio/fileext.h?rev=HEAD&content-type=text/x-cvsweb-markup>
      and <http://www.openbsd.org/cgi-bin/cvsweb/src/lib/libc/stdio/fileext.h?rev=HEAD&content-type=text/x-cvsweb-markup> */
   struct __sfileext
