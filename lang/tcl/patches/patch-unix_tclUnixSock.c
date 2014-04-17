--- unix/tclUnixSock.c.orig	Thu Sep 19 19:04:17 2013
+++ unix/tclUnixSock.c	Thu Apr 17 22:40:39 2014
@@ -665,6 +665,7 @@ TcpHostPortList(
         if (addr.sa4.sin_addr.s_addr == INADDR_ANY) {
             flags |= NI_NUMERICHOST;
         }
+#ifndef __minix
 #ifndef NEED_FAKE_RFC2553
     } else if (addr.sa.sa_family == AF_INET6) {
         if ((IN6_ARE_ADDR_EQUAL(&addr.sa6.sin6_addr,
@@ -677,6 +678,7 @@ TcpHostPortList(
             flags |= NI_NUMERICHOST;
         }
 #endif /* NEED_FAKE_RFC2553 */
+#endif
     }
     /* Check if reverse DNS has been switched off globally */
     if (interp != NULL && Tcl_GetVar(interp, SUPPRESS_RDNS_VAR, 0) != NULL) {
