$NetBSD$

--- libiberty/make-relative-prefix.c.orig	Mon Mar 24 17:11:21 2008
+++ libiberty/make-relative-prefix.c
@@ -57,6 +57,9 @@ relative prefix can be found, return @code{NULL}.
 #ifdef HAVE_UNISTD_H
 #include <unistd.h>
 #endif
+#ifdef HAVE_SYS_STAT_H
+#include <sys/stat.h>
+#endif
 
 #include <string.h>
 
@@ -244,10 +247,15 @@ make_relative_prefix_1 (const char *progname, const ch
 	{
 	  char *startp, *endp, *nstore;
 	  size_t prefixlen = strlen (temp) + 1;
+	  size_t len;
 	  if (prefixlen < 2)
 	    prefixlen = 2;
 
-	  nstore = (char *) alloca (prefixlen + strlen (progname) + 1);
+	  len = prefixlen + strlen (progname) + 1;
+#ifdef HAVE_HOST_EXECUTABLE_SUFFIX
+	  len += strlen (HOST_EXECUTABLE_SUFFIX);
+#endif
+	  nstore = (char *) alloca (len);
 
 	  startp = endp = temp;
 	  while (1)
@@ -262,7 +270,7 @@ make_relative_prefix_1 (const char *progname, const ch
 		    }
 		  else
 		    {
-		      strncpy (nstore, startp, endp - startp);
+		      memcpy (nstore, startp, endp - startp);
 		      if (! IS_DIR_SEPARATOR (endp[-1]))
 			{
 			  nstore[endp - startp] = DIR_SEPARATOR;
@@ -278,8 +286,14 @@ make_relative_prefix_1 (const char *progname, const ch
 #endif
 		      )
 		    {
-		      progname = nstore;
-		      break;
+#if defined (HAVE_SYS_STAT_H) && defined (S_ISREG)
+		      struct stat st;
+		      if (stat (nstore, &st) >= 0 && S_ISREG (st.st_mode))
+#endif
+			{
+			  progname = nstore;
+			  break;
+			}
 		    }
 
 		  if (*endp == 0)
