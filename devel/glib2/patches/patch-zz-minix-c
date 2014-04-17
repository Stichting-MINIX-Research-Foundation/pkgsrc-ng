$NetBSD$

--- glib/gthread-posix.c.orig	Sun Jun  9 22:03:18 2013
+++ glib/gthread-posix.c
@@ -1147,7 +1147,11 @@ g_system_thread_new (GThreadFunc   thread_func,
 void
 g_thread_yield (void)
 {
+#ifdef __minix
+  return;
+#else
   sched_yield ();
+#endif
 }
 
 void
