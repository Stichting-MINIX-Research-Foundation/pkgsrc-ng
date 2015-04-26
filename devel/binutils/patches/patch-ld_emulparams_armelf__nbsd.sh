$NetBSD$

--- ld/emulparams/armelf_nbsd.sh.orig	Tue May 30 16:45:32 2006
+++ ld/emulparams/armelf_nbsd.sh
@@ -3,5 +3,12 @@ MAXPAGESIZE="CONSTANT (MAXPAGESIZE)"
 TEXT_START_ADDR=0x00008000
 TARGET2_TYPE=got-rel
 
+unset DATA_START_SYMBOLS
 unset STACK_ADDR
 unset EMBEDDED
+
+case "$target" in
+  arm*-*-netbsdelf*-*eabi*)
+    LIB_PATH='=/usr/lib/oabi'
+    ;;
+esac
