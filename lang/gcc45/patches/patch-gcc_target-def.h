$NetBSD$

--- gcc/target-def.h.orig	Thu Jun 24 21:06:37 2010
+++ gcc/target-def.h
@@ -706,6 +706,7 @@
    }
 
 #ifndef TARGET_UNWIND_TABLES_DEFAULT
+#error "Missing unwind_tables_default"
 #define TARGET_UNWIND_TABLES_DEFAULT false
 #endif
 
