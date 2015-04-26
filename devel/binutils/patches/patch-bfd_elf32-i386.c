$NetBSD$

--- bfd/elf32-i386.c.orig	Mon Mar 25 08:06:19 2013
+++ bfd/elf32-i386.c
@@ -4976,6 +4976,18 @@ elf_i386_add_symbol_hook (bfd * abfd,
 
 #include "elf32-target.h"
 
+/* MINIX3 support.  */
+
+#undef	TARGET_LITTLE_SYM
+#define	TARGET_LITTLE_SYM		bfd_elf32_i386_minix_vec
+#undef	TARGET_LITTLE_NAME
+#define	TARGET_LITTLE_NAME		"elf32-i386-minix"
+
+#undef	elf32_bed
+#define	elf32_bed				elf32_i386_minix_bed
+
+#include "elf32-target.h"
+
 /* FreeBSD support.  */
 
 #undef	TARGET_LITTLE_SYM
