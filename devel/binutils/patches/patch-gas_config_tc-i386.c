--- gas/config/tc-i386.c.orig	Sun Apr 26 20:11:37 2015
+++ gas/config/tc-i386.c	Sun Apr 26 20:12:12 2015
@@ -317,6 +317,7 @@
 	 && !defined (TE_NETWARE)			\
 	 && !defined (TE_FreeBSD)			\
 	 && !defined (TE_DragonFly)			\
+	 && !defined (TE_MINIX)				\
 	 && !defined (TE_NetBSD)))
 /* This array holds the chars that always start a comment.  If the
    pre-processor is disabled, these aren't very useful.  The option
