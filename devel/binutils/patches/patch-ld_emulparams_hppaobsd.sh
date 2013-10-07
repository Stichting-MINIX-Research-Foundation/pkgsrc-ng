$NetBSD$

--- ld/emulparams/hppaobsd.sh.orig	Tue May 30 16:45:32 2006
+++ ld/emulparams/hppaobsd.sh
@@ -1,4 +1,4 @@
-. ${srcdir}/emulparams/hppanbsd.sh
+. ${srcdir}/emulparams/hppalinux.sh
 
 OUTPUT_FORMAT="elf32-hppa"
 TEXT_START_ADDR=0x1000
