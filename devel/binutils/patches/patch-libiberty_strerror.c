$NetBSD$

--- libiberty/strerror.c.orig	Mon Mar 28 02:09:01 2005
+++ libiberty/strerror.c
@@ -347,7 +347,7 @@ static const struct error_info error_table[] =
   ENTRY(EPROTOTYPE, "EPROTOTYPE", "Protocol wrong type for socket"),
 #endif
 #if defined (ENOPROTOOPT)
-  ENTRY(ENOPROTOOPT, "ENOPROTOOPT", "Protocol not available"),
+  ENTRY(ENOPROTOOPT, "ENOPROTOOPT", "Protocol option not available"),
 #endif
 #if defined (EPROTONOSUPPORT)
   ENTRY(EPROTONOSUPPORT, "EPROTONOSUPPORT", "Protocol not supported"),
