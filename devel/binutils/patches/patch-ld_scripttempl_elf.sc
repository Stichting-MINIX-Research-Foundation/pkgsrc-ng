$NetBSD$

--- ld/scripttempl/elf.sc.orig	Mon Mar 25 08:06:23 2013
+++ ld/scripttempl/elf.sc
@@ -94,6 +94,8 @@
 #
 #  Each of these can also have corresponding .rel.* and .rela.* sections.
 
+test -z "$TEXT_START_SYMBOLS" && TEXT_START_SYMBOLS="PROVIDE_HIDDEN (__eprol = .);"
+test -z "$ENTRY" && ENTRY=_start
 if test -n "$NOP"; then
   FILL="=$NOP"
 else
