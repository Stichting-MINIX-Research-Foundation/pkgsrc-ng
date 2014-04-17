$NetBSD$

--- lib/ipc/common.c.orig	Tue Jan 10 21:53:51 2012
+++ lib/ipc/common.c
@@ -91,7 +91,7 @@ _heim_ipc_create_cred(uid_t uid, gid_t gid, pid_t pid,
     return 0;
 }
 
-#ifndef HAVE_GCD
+#if !defined(HAVE_GCD) && defined(ENABLE_PTHREAD_SUPPORT)
 struct heim_isemaphore {
     HEIMDAL_MUTEX mutex;
     pthread_cond_t cond;
