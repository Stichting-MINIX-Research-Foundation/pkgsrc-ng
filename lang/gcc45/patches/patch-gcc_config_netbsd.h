$NetBSD$

--- gcc/config/netbsd.h.orig	Tue Sep 22 15:11:37 2009
+++ gcc/config/netbsd.h
@@ -37,38 +37,64 @@ along with GCC; see the file COPYING3.  If not see
 
 /* NETBSD_NATIVE is defined when gcc is integrated into the NetBSD
    source tree so it can be configured appropriately without using
-   the GNU configure/build mechanism.  */
+   the GNU configure/build mechanism.
 
-#ifdef NETBSD_NATIVE
+   NETBSD_TOOLS is defined when gcc is built as cross-compiler for
+   the in-tree toolchain.
+ */
 
+#if defined(NETBSD_NATIVE) || defined(NETBSD_TOOLS)
+
 /* Look for the include files in the system-defined places.  */
 
 #undef GPLUSPLUS_INCLUDE_DIR
 #define GPLUSPLUS_INCLUDE_DIR "/usr/include/g++"
 
+#undef GPLUSPLUS_BACKWARD_INCLUDE_DIR
+#define GPLUSPLUS_BACKWARD_INCLUDE_DIR "/usr/include/g++/backward"
+
+/*
+ * XXX figure out a better way to do this
+ */
 #undef GCC_INCLUDE_DIR
-#define GCC_INCLUDE_DIR "/usr/include"
+#define GCC_INCLUDE_DIR "/usr/include/gcc-4.5"
 
 #undef INCLUDE_DEFAULTS
-#define INCLUDE_DEFAULTS			\
-  {						\
-    { GPLUSPLUS_INCLUDE_DIR, "G++", 1, 1 },	\
-    { GCC_INCLUDE_DIR, "GCC", 0, 0 },		\
-    { 0, 0, 0, 0 }				\
+#define INCLUDE_DEFAULTS				\
+  {							\
+    { GPLUSPLUS_INCLUDE_DIR, "G++", 1, 1, 1 },		\
+    { GPLUSPLUS_BACKWARD_INCLUDE_DIR, "G++", 1, 1, 1 },	\
+    { GCC_INCLUDE_DIR, "GCC", 0, 0, 1 },		\
+    { "/usr/include", "GCC", 0, 0, 1 },			\
+    { 0, 0, 0, 0 }					\
   }
 
+/* Under NetBSD, the normal location of the various *crt*.o files is the
+   /usr/lib directory.  */
+
+#undef STANDARD_STARTFILE_PREFIX
+#define STANDARD_STARTFILE_PREFIX	"/usr/lib/"
+#undef STANDARD_STARTFILE_PREFIX_1
+#define STANDARD_STARTFILE_PREFIX_1	"/usr/lib/"
+
+#endif /* NETBSD_NATIVE || NETBSD_TOOLS */
+
+#if defined(NETBSD_NATIVE)
 /* Under NetBSD, the normal location of the compiler back ends is the
    /usr/libexec directory.  */
 
 #undef STANDARD_EXEC_PREFIX
 #define STANDARD_EXEC_PREFIX		"/usr/libexec/"
 
-/* Under NetBSD, the normal location of the various *crt*.o files is the
-   /usr/lib directory.  */
+#undef TOOLDIR_BASE_PREFIX
+#define TOOLDIR_BASE_PREFIX		"../"
 
-#undef STANDARD_STARTFILE_PREFIX
-#define STANDARD_STARTFILE_PREFIX	"/usr/lib/"
+#undef STANDARD_BINDIR_PREFIX
+#define STANDARD_BINDIR_PREFIX		"/usr/bin"
 
+#undef STANDARD_LIBEXEC_PREFIX
+#define STANDARD_LIBEXEC_PREFIX		STANDARD_EXEC_PREFIX
+
 #endif /* NETBSD_NATIVE */
 
 
@@ -97,6 +123,7 @@ along with GCC; see the file COPYING3.  If not see
        %{!pg:-lposix}}		\
      %{p:-lposix_p}		\
      %{pg:-lposix_p}}		\
+   %{shared:-lc}		\
    %{!shared:			\
      %{!symbolic:		\
        %{!p:			\
@@ -110,6 +137,7 @@ along with GCC; see the file COPYING3.  If not see
        %{!pg:-lposix}}		\
      %{p:-lposix_p}		\
      %{pg:-lposix_p}}		\
+   %{shared:-lc}		\
    %{!shared:			\
      %{!symbolic:		\
        %{!p:			\
@@ -121,24 +149,15 @@ along with GCC; see the file COPYING3.  If not see
 #undef LIB_SPEC
 #define LIB_SPEC NETBSD_LIB_SPEC
 
-/* Provide a LIBGCC_SPEC appropriate for NetBSD.  We also want to exclude
-   libgcc with -symbolic.  */
+/* Pass -cxx-isystem to cc1/cc1plus.  */
+#define NETBSD_CC1_AND_CC1PLUS_SPEC		\
+  "%{cxx-isystem}"
 
-#ifdef NETBSD_NATIVE
-#define NETBSD_LIBGCC_SPEC	\
-  "%{!symbolic:			\
-     %{!shared:			\
-       %{!p:			\
-	 %{!pg: -lgcc}}}	\
-     %{shared: -lgcc_pic}	\
-     %{p: -lgcc_p}		\
-     %{pg: -lgcc_p}}"
-#else
-#define NETBSD_LIBGCC_SPEC "%{!shared:%{!symbolic: -lgcc}}"
-#endif
+#undef CC1_SPEC
+#define CC1_SPEC NETBSD_CC1_AND_CC1PLUS_SPEC
 
-#undef LIBGCC_SPEC
-#define LIBGCC_SPEC NETBSD_LIBGCC_SPEC
+#undef CC1PLUS_SPEC
+#define CC1PLUS_SPEC NETBSD_CC1_AND_CC1PLUS_SPEC
 
 /* When building shared libraries, the initialization and finalization 
    functions for the library are .init and .fini respectively.  */
@@ -227,3 +246,7 @@ __enable_execute_stack (void *addr)					\
 
 /* Define this so we can compile MS code for use with WINE.  */
 #define HANDLE_PRAGMA_PACK_PUSH_POP 1
+
+#if defined(HAVE_LD_EH_FRAME_HDR)
+#define LINK_EH_SPEC "--eh-frame-hdr "
+#endif
