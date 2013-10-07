$NetBSD$

--- binutils/objcopy.c.orig	Mon Mar 25 08:06:21 2013
+++ binutils/objcopy.c
@@ -30,6 +30,8 @@
 #include "filenames.h"
 #include "fnmatch.h"
 #include "elf-bfd.h"
+#include <sys/stat.h>
+#include <ctype.h>
 #include "libbfd.h"
 #include "coff/internal.h"
 #include "libcoff.h"
