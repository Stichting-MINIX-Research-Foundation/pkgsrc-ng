$NetBSD$

--- ld/emulparams/elf32_sparc.sh.orig	Mon Sep 20 18:41:15 2010
+++ ld/emulparams/elf32_sparc.sh
@@ -13,6 +13,7 @@ MACHINE=
 TEMPLATE_NAME=elf32
 DATA_PLT=
 GENERATE_SHLIB_SCRIPT=yes
+#ELFSIZE=32
 GENERATE_PIE_SCRIPT=yes
 NOP=0x01000000
 NO_SMALL_DATA=yes
