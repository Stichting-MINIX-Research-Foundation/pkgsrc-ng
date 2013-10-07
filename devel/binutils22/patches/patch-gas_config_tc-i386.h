$NetBSD$

--- gas/config/tc-i386.h.orig	Mon Aug  1 23:04:22 2011
+++ gas/config/tc-i386.h
@@ -68,6 +68,10 @@ extern unsigned long i386_mach (void);
 #define ELF_TARGET_FORMAT64	"elf64-x86-64-sol2"
 #endif
 
+#ifdef TE_MINIX
+#define ELF_TARGET_FORMAT      "elf32-i386-minix"
+#endif
+
 #ifndef ELF_TARGET_FORMAT
 #define ELF_TARGET_FORMAT	"elf32-i386"
 #endif
