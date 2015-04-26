$NetBSD$

--- ld/ldlex.h.orig	Mon Mar 25 08:06:23 2013
+++ ld/ldlex.h
@@ -136,6 +136,7 @@ enum option_values
 #endif /* ENABLE_PLUGINS */
   OPTION_DEFAULT_SCRIPT,
   OPTION_PRINT_OUTPUT_FORMAT,
+  OPTION_IGNORE_UNRESOLVED_SYMBOL
 };
 
 /* The initial parser states.  */
