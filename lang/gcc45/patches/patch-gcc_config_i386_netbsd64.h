$NetBSD$

--- gcc/config/i386/netbsd64.h.orig	Thu Aug  2 10:49:31 2007
+++ gcc/config/i386/netbsd64.h
@@ -70,3 +70,7 @@ along with GCC; see the file COPYING3.  If not see
 #define ENABLE_EXECUTE_STACK NETBSD_ENABLE_EXECUTE_STACK
 
 #define TARGET_VERSION fprintf (stderr, " (NetBSD/x86_64 ELF)");
+
+/* Preserve i386 psABI  */
+#undef PREFERRED_STACK_BOUNDARY_DEFAULT
+#define PREFERRED_STACK_BOUNDARY_DEFAULT MIN_STACK_BOUNDARY
