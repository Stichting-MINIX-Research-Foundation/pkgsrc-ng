$NetBSD$

--- binutils/bucomm.c.orig	Fri Jun 29 12:59:49 2012
+++ binutils/bucomm.c
@@ -580,7 +580,14 @@ get_file_size (const char * file_name)
 		   file_name, strerror (errno));
     }  
   else if (! S_ISREG (statbuf.st_mode))
-    non_fatal (_("Warning: '%s' is not an ordinary file"), file_name);
+    {
+      if (!S_ISCHR(statbuf.st_mode))
+	{
+	  non_fatal (_("Warning: '%s' is not an ordinary file"), file_name);
+	  return 0;
+	}
+      return statbuf.st_size ? statbuf.st_size : 1;
+    }
   else if (statbuf.st_size < 0)
     non_fatal (_("Warning: '%s' has negative size, probably it is too large"),
                file_name);
