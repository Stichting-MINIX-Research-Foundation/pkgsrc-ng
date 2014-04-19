--- lib/connect.c.orig	Fri Apr 18 15:48:42 2014
+++ lib/connect.c	Fri Apr 18 15:49:19 2014
@@ -506,7 +506,7 @@ static bool verifyconnect(curl_socket_t sockfd, int *e
     err = 0;
   }
 #endif
-#ifdef __minix
+#if defined EBADIOCTL && defined __minix
   /* Minix 3.1.x doesn't support getsockopt on UDP sockets */
   if(EBADIOCTL == err) {
     SET_SOCKERRNO(0);
