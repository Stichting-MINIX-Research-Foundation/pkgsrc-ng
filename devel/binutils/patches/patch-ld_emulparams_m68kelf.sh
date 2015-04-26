$NetBSD$

--- ld/emulparams/m68kelf.sh.orig	Tue Sep 29 16:28:52 2009
+++ ld/emulparams/m68kelf.sh
@@ -10,5 +10,6 @@ NOP=0x4e714e71
 TEMPLATE_NAME=elf32
 EXTRA_EM_FILE=m68kelf
 GENERATE_SHLIB_SCRIPT=yes
+ELFSIZE=32
 GENERATE_PIE_SCRIPT=yes
 NO_SMALL_DATA=yes
