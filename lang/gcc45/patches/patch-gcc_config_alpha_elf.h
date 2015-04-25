$NetBSD$

--- gcc/config/alpha/elf.h.orig	Wed Jun 30 15:16:54 2010
+++ gcc/config/alpha/elf.h
@@ -25,8 +25,9 @@ along with GCC; see the file COPYING3.  If not see
 
 /* ??? Move all SDB stuff from alpha.h to osf.h.  */
 #undef SDB_DEBUGGING_INFO
+#undef MIPS_DEBUGGING_INFO
+#undef DBX_DEBUGGING_INFO
 
-#define DBX_DEBUGGING_INFO 1
 #define DWARF2_DEBUGGING_INFO 1
 
 #undef  PREFERRED_DEBUGGING_TYPE
@@ -440,7 +441,7 @@ extern int alpha_this_gpdisp_sequence_number;
    As of Jan 2002, only glibc 2.2.4 can actually make use of this, but
    I imagine that other systems will catch up.  In the meantime, it
    doesn't harm to make sure that the data exists to be used later.  */
-#if defined(HAVE_LD_EH_FRAME_HDR)
+#if defined(HAVE_LD_EH_FRAME_HDR) && !defined(LINK_EH_SPEC)
 #define LINK_EH_SPEC "%{!static:--eh-frame-hdr} "
 #endif
 
