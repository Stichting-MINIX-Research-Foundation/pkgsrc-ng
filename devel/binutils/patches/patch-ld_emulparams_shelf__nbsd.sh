$NetBSD$

--- ld/emulparams/shelf_nbsd.sh.orig	Tue Jan 15 23:05:46 2008
+++ ld/emulparams/shelf_nbsd.sh
@@ -9,7 +9,11 @@ MAXPAGESIZE="CONSTANT (MAXPAGESIZE)"
 
 DATA_START_SYMBOLS='PROVIDE (__data_start = .);';
 
-ENTRY=_start
+ENTRY=__start
 
 unset EMBEDDED
 unset OTHER_SECTIONS
+
+OTHER_READWRITE_SECTIONS='
+  .note.ABI-tag : { *(.note.ABI-tag) }
+'
