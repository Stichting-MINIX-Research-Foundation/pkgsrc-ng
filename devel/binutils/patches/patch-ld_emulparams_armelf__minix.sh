$NetBSD$

--- ld/emulparams/armelf_minix.sh.orig	Mon May 19 14:12:58 2014
+++ ld/emulparams/armelf_minix.sh
@@ -0,0 +1,15 @@
+. ${srcdir}/emulparams/armelf.sh
+. ${srcdir}/emulparams/elf_minix.sh
+OUTPUT_FORMAT="elf32-littlearm"
+MAXPAGESIZE="CONSTANT (MAXPAGESIZE)"
+COMMONPAGESIZE="CONSTANT (COMMONPAGESIZE)"
+
+DATA_START_SYMBOLS='PROVIDE (__data_start = .);';
+
+# Dynamic libraries support
+GENERATE_SHLIB_SCRIPT=yes
+TARGET2_TYPE=got-rel
+
+GENERATE_PIE_SCRIPT=yes
+
+unset EMBEDDED
