$NetBSD$

--- gprof/gprof.c.orig	Fri Jun 12 15:33:30 2009
+++ gprof/gprof.c
@@ -47,6 +47,8 @@
 
 static void usage (FILE *, int) ATTRIBUTE_NORETURN;
 
+#include <stdlib.h>
+
 const char * whoami;
 const char * function_mapping_file;
 static const char * external_symbol_table;
