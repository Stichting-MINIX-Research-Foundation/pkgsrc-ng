$NetBSD$

--- ld/emulparams/elf64alpha_nbsd.sh.orig	Mon Dec 17 23:54:58 2001
+++ ld/emulparams/elf64alpha_nbsd.sh
@@ -1,2 +1,8 @@
 . ${srcdir}/emulparams/elf64alpha.sh
 ENTRY=__start
+
+NOP=0x47ff041f
+# XXX binutils 2.13
+# Note that the number is always big-endian, thus we have to 
+# reverse the digit string.
+#NOP=0x0000fe2f1f04ff47		# unop; nop
