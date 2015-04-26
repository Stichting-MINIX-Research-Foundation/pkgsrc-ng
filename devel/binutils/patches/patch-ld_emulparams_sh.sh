$NetBSD$

--- ld/emulparams/sh.sh.orig	Thu Nov 22 09:08:04 2001
+++ ld/emulparams/sh.sh
@@ -3,6 +3,6 @@
 
 SCRIPT_NAME=sh
 OUTPUT_FORMAT="coff-sh"
-TEXT_START_ADDR=0x8000
-TARGET_PAGE_SIZE=128
+TEXT_START_ADDR=0x1000
+TARGET_PAGE_SIZE=0x1000
 ARCH=sh
