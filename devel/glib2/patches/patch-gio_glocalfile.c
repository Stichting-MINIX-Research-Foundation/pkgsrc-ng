--- ./gio/glocalfile.c.orig	Tue Nov 12 05:30:22 2013
+++ ./gio/glocalfile.c	Fri May  9 12:26:13 2014
@@ -89,6 +89,10 @@
 #endif
 #endif
 
+#ifdef __minix
+/* LSC: Not very proud of that one, but... */
+#undef AT_FDCWD
+#endif
 
 static void g_local_file_file_iface_init (GFileIface *iface);
 
@@ -2699,7 +2703,11 @@ g_local_file_measure_size_of_file (gint           pare
         return FALSE;
 
 #ifdef AT_FDCWD
+#ifdef O_DIRECTORY
       dir_fd = openat (parent_fd, name->data, O_RDONLY | O_DIRECTORY);
+#else
+      dir_fd = openat (parent_fd, name->data, O_RDONLY);
+#endif
       if (dir_fd < 0)
         return g_local_file_measure_size_error (state->flags, errno, name, error);
 #endif
