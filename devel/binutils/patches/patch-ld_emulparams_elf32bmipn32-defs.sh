$NetBSD$

--- ld/emulparams/elf32bmipn32-defs.sh.orig	Tue Sep  4 14:14:28 2012
+++ ld/emulparams/elf32bmipn32-defs.sh
@@ -6,6 +6,7 @@ SCRIPT_NAME=elf
 
 # Handle both big- and little-ended 32-bit MIPS objects.
 ARCH=mips
+MACHINE=
 OUTPUT_FORMAT="elf32-bigmips"
 BIG_OUTPUT_FORMAT="elf32-bigmips"
 LITTLE_OUTPUT_FORMAT="elf32-littlemips"
