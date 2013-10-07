$NetBSD$

--- ld/ldmain.h.orig	Fri Jul 13 13:20:26 2012
+++ ld/ldmain.h
@@ -41,6 +41,7 @@ extern int overflow_cutoff_limit;
 
 extern void add_ysym (const char *);
 extern void add_wrap (const char *);
+extern void add_ignoresym (const char *);
 extern void add_keepsyms_file (const char *);
 
 #endif
