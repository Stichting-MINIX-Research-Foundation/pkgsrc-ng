$NetBSD$

--- lib/krb5/get_addrs.c.orig	Tue Jan 10 21:53:51 2012
+++ lib/krb5/get_addrs.c
@@ -189,9 +189,11 @@ find_all_addresses (krb5_context context, krb5_address
 		continue;
 	    if (!krb5_sockaddr_is_loopback(ifa->ifa_addr))
 		continue;
+#ifdef IFF_LOOPBACK
 	    if ((ifa->ifa_flags & IFF_LOOPBACK) == 0)
 		/* Presumably loopback addrs are only used on loopback ifs! */
 		continue;
+#endif
 	    ret = krb5_sockaddr2address(context,
 					ifa->ifa_addr, &res->val[idx]);
 	    if (ret)
