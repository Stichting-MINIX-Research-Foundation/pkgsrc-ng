$NetBSD$

--- e_os.h.orig	Mon Feb 11 15:26:04 2013
+++ e_os.h
@@ -79,7 +79,11 @@ extern "C" {
 #ifndef DEVRANDOM
 /* set this to a comma-separated list of 'random' device files to try out.
  * My default, we will try to read at least one of these files */
+#ifdef __minix
+#define DEVRANDOM "/dev/random","/dev/urandom","/dev/srandom"
+#else
 #define DEVRANDOM "/dev/urandom","/dev/random","/dev/srandom"
+#endif /* __minix */
 #endif
 #ifndef DEVRANDOM_EGD
 /* set this to a comma-seperated list of 'egd' sockets to try out. These
