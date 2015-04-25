$NetBSD$

--- gcc/config/arm/elf.h.orig	Sun Jun 21 20:48:15 2009
+++ gcc/config/arm/elf.h
@@ -161,6 +161,8 @@
 #undef L_floatdidf
 #undef L_floatdisf
 #undef L_floatundidf
+/* XXXMRG: don't take this out, we need it! */
+# ifndef __NetBSD__
 #undef L_floatundisf
+# endif
 #endif
-
