$NetBSD: patch-src_common_compat__getopt__main.c,v 1.2 2014/03/14 20:49:56 gdt Exp $

See comment in patch-src_common_compat__getopt.h.  In addition, a
kludge is added here to get the test file to build, pending a new
release from upstream with the issue properly addressed.

--- src/common/compat_getopt_main.c.orig	2012-12-04 14:43:40.000000000 +0000
+++ src/common/compat_getopt_main.c
@@ -173,6 +173,8 @@ main(int argc, char * argv[])
               progname);
     }
 
+#define getopt_long_only getopt_long
+
   /* parse all options from the command line */
   while ((opt =
           getopt_long_only(argc, argv, shortopts, longopts, &longind)) != -1)
