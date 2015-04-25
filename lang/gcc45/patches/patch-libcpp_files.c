$NetBSD$

--- libcpp/files.c.orig	Tue Sep 22 08:37:31 2009
+++ libcpp/files.c
@@ -30,6 +30,7 @@ along with this program; see the file COPYING3.  If no
 #include "obstack.h"
 #include "hashtab.h"
 #include "md5.h"
+#include "../gcc/defaults.h"
 #include <dirent.h>
 
 /* Variable length record files on VMS will have a stat size that includes
@@ -219,20 +220,32 @@ static bool check_file_against_entries (cpp_reader *, 
 static bool
 open_file (_cpp_file *file)
 {
+  const char *cpp_restricted;
+
+  GET_ENVIRONMENT(cpp_restricted, "CPP_RESTRICTED");
+
   if (file->path[0] == '\0')
     {
       file->fd = 0;
       set_stdin_to_binary_mode ();
     }
   else
-    file->fd = open (file->path, O_RDONLY | O_NOCTTY | O_BINARY, 0666);
+    file->fd = open (file->path, O_RDONLY | O_NOCTTY | O_BINARY
+		     | (cpp_restricted != NULL) ? O_NONBLOCK : 0, 0666);
 
+
   if (file->fd != -1)
     {
       if (fstat (file->fd, &file->st) == 0)
 	{
 	  if (!S_ISDIR (file->st.st_mode))
+	  if (cpp_restricted != NULL
+	      ? S_ISREG (file->st.st_mode) : !S_ISDIR (file->st.st_mode))
+
 	    {
+	      if (cpp_restricted)
+		fcntl(file->fd, F_SETFL,
+		      fcntl(file->fd, F_GETFL, 0) & ~O_NONBLOCK);
 	      file->err_no = 0;
 	      return true;
 	    }
