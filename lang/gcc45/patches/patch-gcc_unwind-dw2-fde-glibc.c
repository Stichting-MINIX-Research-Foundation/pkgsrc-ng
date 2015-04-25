$NetBSD$

--- gcc/unwind-dw2-fde-glibc.c.orig	Wed Nov 25 10:55:54 2009
+++ gcc/unwind-dw2-fde-glibc.c
@@ -57,6 +57,12 @@
 # define USE_PT_GNU_EH_FRAME
 #endif
 
+#if !defined(inhibit_libc) && defined(HAVE_LD_EH_FRAME_HDR) \
+    && defined(__NetBSD__)
+# define ElfW(n) Elf_##n
+# define USE_PT_GNU_EH_FRAME
+#endif
+
 #if defined(USE_PT_GNU_EH_FRAME)
 
 #ifndef __RELOC_POINTER
