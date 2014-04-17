$NetBSD$

--- lib/ipc/server.c.orig	Tue Jan 10 21:53:51 2012
+++ lib/ipc/server.c
@@ -525,6 +525,7 @@ update_client_creds(struct client *c)
 	}
     }
 #endif
+#ifndef __minix
 #ifdef SO_PEERCRED
     /* Linux */
     {
@@ -538,6 +539,7 @@ update_client_creds(struct client *c)
 	    return 1;
 	}
     }
+#endif
 #endif
 #if defined(LOCAL_PEERCRED) && defined(XUCRED_VERSION)
     {
