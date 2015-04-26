$NetBSD$

--- gas/config/tc-m68k.c.orig	Wed May 16 10:26:47 2012
+++ gas/config/tc-m68k.c
@@ -7426,12 +7426,12 @@ m68k_lookup_cpu (const char *arg, const struct m68k_cp
 	}
     }
   
-  /* Remove 'm' or 'mc' prefix from 68k variants.  */
+  /* Remove 'm' or 'mc' prefix from 68k or coldfire variants.  */
   if (allow_m)
     {
       if (arg[0] == 'm')
 	{
-	  if (arg[1] == '6')
+	  if (arg[1] == '6' || arg[1] == '5')
 	    arg += 1;
 	  else if (arg[1] == 'c'  && arg[2] == '6')
 	    arg += 2;
