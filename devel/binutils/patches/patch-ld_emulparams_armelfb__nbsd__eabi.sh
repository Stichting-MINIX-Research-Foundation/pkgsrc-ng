$NetBSD$

--- ld/emulparams/armelfb_nbsd_eabi.sh.orig	Mon May 19 14:12:58 2014
+++ ld/emulparams/armelfb_nbsd_eabi.sh
@@ -0,0 +1,2 @@
+. ${srcdir}/emulparams/armelf_nbsd_eabi.sh
+OUTPUT_FORMAT="elf32-bigarm"
