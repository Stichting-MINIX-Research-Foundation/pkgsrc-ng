$NetBSD$

--- ld/emulparams/m68kelfnbsd.sh.orig	Tue Dec 18 13:26:26 2001
+++ ld/emulparams/m68kelfnbsd.sh
@@ -1,4 +1,4 @@
 . ${srcdir}/emulparams/m68kelf.sh
 TEXT_START_ADDR=0x2000
 TARGET_PAGE_SIZE=0x2000
-MACHINE=
+NONPAGED_TEXT_START_ADDR=${TEXT_START_ADDR}
