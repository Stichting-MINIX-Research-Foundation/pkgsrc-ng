$NetBSD$

--- binutils/dwarf.c.orig	Mon Jul  2 14:35:33 2012
+++ binutils/dwarf.c
@@ -29,6 +29,7 @@
 #include "dwarf2.h"
 #include "dwarf.h"
 #include "gdb/gdb-index.h"
+#include "getopt.h"
 
 static const char *regname (unsigned int regno, int row);
 
