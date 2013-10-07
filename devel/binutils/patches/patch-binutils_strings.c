$NetBSD$

--- binutils/strings.c.orig	Thu Feb  9 04:51:44 2012
+++ binutils/strings.c
@@ -598,7 +598,7 @@ print_strings (const char *filename, FILE *stream, fil
 	    else
 #elif !BFD_HOST_64BIT_LONG
 	    if (start != (unsigned long) start)
-	      printf ("++%7ld ", (unsigned long) start);
+	      printf ("++%7llu ", (unsigned long) start);
 	    else
 #endif
 	      printf ("%7ld ", (long) start);
