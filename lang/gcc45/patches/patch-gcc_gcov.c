$NetBSD$

--- gcc/gcov.c.orig	Sat Jan  9 00:00:42 2010
+++ gcc/gcov.c
@@ -58,6 +58,10 @@ along with Gcov; see the file COPYING3.  If not see
 
 #define STRING_SIZE 200
 
+#if defined(__minix)
+#define block_t gcc_block_t
+#endif
+
 struct function_info;
 struct block_info;
 struct source_info;
