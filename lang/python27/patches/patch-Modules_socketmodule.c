--- Modules/socketmodule.c.orig	Sun Nov 10 07:36:41 2013
+++ Modules/socketmodule.c	Fri Apr 18 18:50:49 2014
@@ -182,7 +182,7 @@ shutdown(how) -- shut down traffic in one or both dire
    (this includes the getaddrinfo emulation) protect access with a lock. */
 #if defined(WITH_THREAD) && (defined(__APPLE__) || \
     (defined(__FreeBSD__) && __FreeBSD_version+0 < 503000) || \
-    defined(__OpenBSD__) || defined(__NetBSD__) || \
+    defined(__OpenBSD__) || defined(__NetBSD__) || defined(__minix) || \
     defined(__VMS) || !defined(HAVE_GETADDRINFO))
 #define USE_GETADDRINFO_LOCK
 #endif
@@ -380,7 +380,7 @@ const char *inet_ntop(int af, const void *src, char *d
 #define SOCKETCLOSE close
 #endif
 
-#if (defined(HAVE_BLUETOOTH_H) || defined(HAVE_BLUETOOTH_BLUETOOTH_H)) && !defined(__NetBSD__) && !defined(__DragonFly__)
+#if (defined(HAVE_BLUETOOTH_H) || defined(HAVE_BLUETOOTH_BLUETOOTH_H)) && !defined(__NetBSD__) && !defined(__DragonFly__) && !defined(__minix)
 #define USE_BLUETOOTH 1
 #if defined(__FreeBSD__)
 #define BTPROTO_L2CAP BLUETOOTH_PROTO_L2CAP
@@ -394,7 +394,7 @@ const char *inet_ntop(int af, const void *src, char *d
 #define _BT_L2_MEMB(sa, memb) ((sa)->l2cap_##memb)
 #define _BT_RC_MEMB(sa, memb) ((sa)->rfcomm_##memb)
 #define _BT_HCI_MEMB(sa, memb) ((sa)->hci_##memb)
-#elif defined(__NetBSD__) || defined(__DragonFly__)
+#elif defined(__NetBSD__) || defined(__DragonFly__) || defined(__minix)
 #define sockaddr_l2 sockaddr_bt
 #define sockaddr_rc sockaddr_bt
 #define sockaddr_hci sockaddr_bt
@@ -1132,7 +1132,7 @@ makesockaddr(int sockfd, struct sockaddr *addr, int ad
         case BTPROTO_HCI:
         {
             struct sockaddr_hci *a = (struct sockaddr_hci *) addr;
-#if defined(__NetBSD__) || defined(__DragonFly__)
+#if defined(__NetBSD__) || defined(__DragonFly__) || defined(__minix)
             return makebdaddr(&_BT_HCI_MEMB(a, bdaddr));
 #else
             PyObject *ret = NULL;
@@ -1429,7 +1429,7 @@ getsockaddrarg(PySocketSockObject *s, PyObject *args,
         case BTPROTO_HCI:
         {
             struct sockaddr_hci *addr = (struct sockaddr_hci *)addr_ret;
-#if defined(__NetBSD__) || defined(__DragonFly__)
+#if defined(__NetBSD__) || defined(__DragonFly__) || defined(__minix)
 			char *straddr = PyBytes_AS_STRING(args);
 
 			_BT_HCI_MEMB(addr, family) = AF_BLUETOOTH;
@@ -2742,6 +2742,10 @@ sock_recvfrom_into(PySocketSockObject *s, PyObject *ar
     if (recvlen == 0) {
         /* If nbytes was not specified, use the buffer's length */
         recvlen = buflen;
+    } else if (recvlen > buflen) {
+        PyErr_SetString(PyExc_ValueError,
+                        "nbytes is greater than the length of the buffer");
+        goto error;
     }
 
     readlen = sock_recvfrom_guts(s, buf.buf, recvlen, flags, &addr);
@@ -4772,11 +4776,11 @@ init_socket(void)
     PyModule_AddIntConstant(m, "BTPROTO_L2CAP", BTPROTO_L2CAP);
     PyModule_AddIntConstant(m, "BTPROTO_HCI", BTPROTO_HCI);
     PyModule_AddIntConstant(m, "SOL_HCI", SOL_HCI);
-#if !defined(__NetBSD__) && !defined(__DragonFly__)
+#if !defined(__NetBSD__) && !defined(__DragonFly__) && !defined(__minix)
     PyModule_AddIntConstant(m, "HCI_FILTER", HCI_FILTER);
 #endif
 #if !defined(__FreeBSD__)
-#if !defined(__NetBSD__) && !defined(__DragonFly__)
+#if !defined(__NetBSD__) && !defined(__DragonFly__) && !defined(__minix)
     PyModule_AddIntConstant(m, "HCI_TIME_STAMP", HCI_TIME_STAMP);
 #endif
     PyModule_AddIntConstant(m, "HCI_DATA_DIR", HCI_DATA_DIR);
