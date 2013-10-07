$NetBSD$

--- ld/emulparams/elf_i386.sh.orig	Mon Jun 11 13:23:50 2012
+++ ld/emulparams/elf_i386.sh
@@ -9,7 +9,14 @@ ARCH=i386
 MACHINE=
 TEMPLATE_NAME=elf32
 GENERATE_SHLIB_SCRIPT=yes
+#ELFSIZE=32
 GENERATE_PIE_SCRIPT=yes
 NO_SMALL_DATA=yes
 SEPARATE_GOTPLT="SIZEOF (.got.plt) >= 12 ? 12 : 0"
 IREL_IN_PLT=
+
+case "$target" in
+  x86_64-*-netbsd*)
+    LIB_PATH='=/usr/lib/i386'
+    ;;
+esac
