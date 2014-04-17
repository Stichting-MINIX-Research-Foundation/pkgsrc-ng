$NetBSD$

--- glib/glib/gthread-posix.c.orig	Tue Oct  2 05:49:07 2012
+++ glib/glib/gthread-posix.c
@@ -1143,7 +1143,11 @@ g_system_thread_new (GThreadFunc   thread_func,
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
