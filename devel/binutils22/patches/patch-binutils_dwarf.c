$NetBSD$

--- binutils/dwarf.c.orig	Sun Sep 18 16:50:17 2011
+++ binutils/dwarf.c
@@ -28,6 +28,7 @@
 #include "elf/common.h"
 #include "dwarf2.h"
 #include "dwarf.h"
+#include "getopt.h"
 
 static const char *regname (unsigned int regno, int row);
 
