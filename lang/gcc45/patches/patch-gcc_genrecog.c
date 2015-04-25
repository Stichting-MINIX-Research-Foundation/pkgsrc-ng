$NetBSD$

--- gcc/genrecog.c.orig	Mon Jun 22 10:29:13 2009
+++ gcc/genrecog.c
@@ -1849,11 +1849,13 @@ write_afterward (struct decision *start, struct decisi
 static void
 print_host_wide_int (HOST_WIDE_INT val)
 {
+  /* XXX: the "min" below is computed for build, not host!!! */
   HOST_WIDE_INT min = (unsigned HOST_WIDE_INT)1 << (HOST_BITS_PER_WIDE_INT-1);
   if (val == min)
-    printf ("(" HOST_WIDE_INT_PRINT_DEC_C "-1)", val + 1);
+    printf ("(HOST_WIDE_INT_CONSTANT (" HOST_WIDE_INT_PRINT_DEC ")-1)",
+            val + 1);
   else
-    printf (HOST_WIDE_INT_PRINT_DEC_C, val);
+    printf ("HOST_WIDE_INT_CONSTANT (" HOST_WIDE_INT_PRINT_DEC")", val);
 }
 
 /* Emit a switch statement, if possible, for an initial sequence of
