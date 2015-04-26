$NetBSD$

--- bfd/bfd-in2.h.orig	Tue Sep  4 12:53:41 2012
+++ bfd/bfd-in2.h
@@ -5788,6 +5788,11 @@ struct bfd
   /* This BFD has been created by the linker and doesn't correspond
      to any input file.  */
 #define BFD_LINKER_CREATED 0x2000
+  /* This may be set before writing out a BFD to request that it
+  be written using values for UIDs, GIDs, timestamps, etc. that
+  will be consistent from run to run.  */
+#define BFD_DETERMINISTIC_OUTPUT 0x4000
+
 
   /* This may be set before writing out a BFD to request that it
      be written using values for UIDs, GIDs, timestamps, etc. that
