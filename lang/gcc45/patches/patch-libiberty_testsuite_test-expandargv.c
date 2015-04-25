$NetBSD$

--- libiberty/testsuite/test-expandargv.c.orig	Thu Oct  8 15:14:41 2009
+++ libiberty/testsuite/test-expandargv.c
@@ -189,7 +189,7 @@ writeout_test (int test, const char * test_data)
 {
   char filename[256];
   FILE *fd;
-  size_t len;
+  size_t len, sys_fwrite;
   char * parse;
 
   /* Unique filename per test */
@@ -208,7 +208,10 @@ writeout_test (int test, const char * test_data)
   /* Run all possible replaces */
   run_replaces (parse);
 
-  fwrite (parse, len, sizeof (char), fd);
+  sys_fwrite = fwrite (parse, sizeof (char), len, fd);
+  if (sys_fwrite != len)
+    fatal_error (__LINE__, "Failed to write to test file.", errno);
+
   free (parse);
   fclose (fd);
 }
