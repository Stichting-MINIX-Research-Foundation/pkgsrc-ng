$NetBSD$

--- gcc/config/rs6000/sysv4.h.orig	Wed Nov  3 13:55:26 2010
+++ gcc/config/rs6000/sysv4.h
@@ -120,7 +120,12 @@ do {									\
   else if (!strcmp (rs6000_abi_name, "gnu"))				\
     rs6000_current_abi = ABI_V4;					\
   else if (!strcmp (rs6000_abi_name, "netbsd"))				\
-    rs6000_current_abi = ABI_V4;					\
+    {									\
+      if (TARGET_64BIT)							\
+	rs6000_current_abi = ABI_AIX;					\
+      else								\
+  	rs6000_current_abi = ABI_V4;					\
+    }									\
   else if (!strcmp (rs6000_abi_name, "openbsd"))			\
     rs6000_current_abi = ABI_V4;					\
   else if (!strcmp (rs6000_abi_name, "i960-old"))			\
@@ -618,6 +623,7 @@ SVR4_ASM_SPEC \
 #endif
 
 /* Pass -G xxx to the compiler and set correct endian mode.  */
+#undef CC1_SPEC
 #define	CC1_SPEC "%{G*} %(cc1_cpu) \
 %{mlittle|mlittle-endian: %(cc1_endian_little);           \
   mbig   |mbig-endian   : %(cc1_endian_big);              \
@@ -641,7 +647,8 @@ SVR4_ASM_SPEC \
 %{msdata: -msdata=default} \
 %{mno-sdata: -msdata=none} \
 %{!mbss-plt: %{!msecure-plt: %(cc1_secure_plt_default)}} \
-%{profile: -p}"
+%{profile: -p} \
+%(cc1_os_netbsd)"
 
 /* Don't put -Y P,<path> for cross compilers.  */
 #ifndef CROSS_DIRECTORY_STRUCTURE
@@ -913,7 +920,7 @@ SVR4_ASM_SPEC \
   %{rdynamic:-export-dynamic} \
   %{!dynamic-linker:-dynamic-linker " LINUX_DYNAMIC_LINKER "}}}"
 
-#if defined(HAVE_LD_EH_FRAME_HDR)
+#if defined(HAVE_LD_EH_FRAME_HDR) && !defined(LINK_EH_SPEC)
 # define LINK_EH_SPEC "%{!static:--eh-frame-hdr} "
 #endif
 
@@ -950,28 +957,23 @@ SVR4_ASM_SPEC \
 -Asystem=gnu -Asystem=unix -Asystem=posix %{pthread:-D_REENTRANT}"
 
 /* NetBSD support.  */
-#define LIB_NETBSD_SPEC "\
-%{profile:-lgmon -lc_p} %{!profile:-lc}"
+#define LIB_NETBSD_SPEC NETBSD_LIB_SPEC
 
-#define	STARTFILE_NETBSD_SPEC "\
-ncrti.o%s crt0.o%s \
-%{!shared:crtbegin.o%s} %{shared:crtbeginS.o%s}"
+#define	STARTFILE_NETBSD_SPEC NETBSD_STARTFILE_SPEC
 
-#define ENDFILE_NETBSD_SPEC "\
-%{!shared:crtend.o%s} %{shared:crtendS.o%s} \
-ncrtn.o%s"
+#define ENDFILE_NETBSD_SPEC NETBSD_ENDFILE_SPEC
 
 #define LINK_START_NETBSD_SPEC "\
 "
 
-#define LINK_OS_NETBSD_SPEC "\
-%{!shared: %{!static: \
-  %{rdynamic:-export-dynamic} \
-  %{!dynamic-linker:-dynamic-linker /usr/libexec/ld.elf_so}}}"
+#define LINK_OS_NETBSD_SPEC NETBSD_LINK_SPEC_ELF
 
 #define CPP_OS_NETBSD_SPEC "\
 -D__powerpc__ -D__NetBSD__ -D__KPRINTF_ATTRIBUTE__"
 
+#define CC1_OS_NETBSD_SPEC "\
+%{cxx-isystem}"
+
 /* OpenBSD support.  */
 #ifndef	LIB_OPENBSD_SPEC
 #define LIB_OPENBSD_SPEC "%{!shared:%{pthread:-lpthread%{p:_p}%{!p:%{pg:_p}}}} %{!shared:-lc%{p:_p}%{!p:%{pg:_p}}}"
@@ -1064,6 +1066,7 @@ ncrtn.o%s"
   { "cc1_endian_little",	CC1_ENDIAN_LITTLE_SPEC },		\
   { "cc1_endian_default",	CC1_ENDIAN_DEFAULT_SPEC },		\
   { "cc1_secure_plt_default",	CC1_SECURE_PLT_DEFAULT_SPEC },		\
+  { "cc1_os_netbsd",		CC1_OS_NETBSD_SPEC },			\
   { "cpp_os_ads",		CPP_OS_ADS_SPEC },			\
   { "cpp_os_yellowknife",	CPP_OS_YELLOWKNIFE_SPEC },		\
   { "cpp_os_mvme",		CPP_OS_MVME_SPEC },			\
