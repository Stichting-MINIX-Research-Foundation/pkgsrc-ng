$NetBSD$

--- libcpp/init.c.orig	Thu Feb 11 19:49:17 2010
+++ libcpp/init.c
@@ -25,7 +25,9 @@ along with this program; see the file COPYING3.  If no
 #include "cpplib.h"
 #include "internal.h"
 #include "mkdeps.h"
+#ifdef ENABLE_NLS
 #include "localedir.h"
+#endif
 
 static void init_library (void);
 static void mark_named_operators (cpp_reader *, int);
