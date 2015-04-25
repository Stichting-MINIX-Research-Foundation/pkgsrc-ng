$NetBSD$

--- gcc/config/netbsd-elf.h.orig	Mon Sep  3 16:14:04 2007
+++ gcc/config/netbsd-elf.h
@@ -52,8 +52,11 @@ along with GCC; see the file COPYING3.  If not see
        %{!p:crt0%O%s}}}		\
    %:if-exists(crti%O%s)	\
    %{static:%:if-exists-else(crtbeginT%O%s crtbegin%O%s)} \
-   %{!static: \
-     %{!shared:crtbegin%O%s} %{shared:crtbeginS%O%s}}"
+   %{!static:                   \
+     %{!shared:                 \
+       %{!pie:crtbegin%O%s}     \
+       %{pie:crtbeginS%O%s}}    \
+     %{shared:crtbeginS%O%s}}"
 
 #undef STARTFILE_SPEC
 #define STARTFILE_SPEC NETBSD_STARTFILE_SPEC
@@ -64,7 +67,10 @@ along with GCC; see the file COPYING3.  If not see
    C++ file-scope static objects deconstructed after exiting "main".  */
 
 #define NETBSD_ENDFILE_SPEC	\
-  "%{!shared:crtend%O%s} %{shared:crtendS%O%s} \
+  "%{!shared:                   \
+    %{!pie:crtend%O%s}          \
+    %{pie:crtendS%O%s}}         \
+   %{shared:crtendS%O%s}        \
    %:if-exists(crtn%O%s)"
 
 #undef ENDFILE_SPEC
@@ -82,6 +88,7 @@ along with GCC; see the file COPYING3.  If not see
 #define NETBSD_LINK_SPEC_ELF \
   "%{assert*} %{R*} %{rpath*} \
    %{shared:-shared} \
+   %{symbolic:-Bsymbolic} \
    %{!shared: \
      -dc -dp \
      %{!nostdlib: \
@@ -96,3 +103,11 @@ along with GCC; see the file COPYING3.  If not see
 #ifdef HAVE_LD_AS_NEEDED
 #define USE_LD_AS_NEEDED 1
 #endif
+
+#define MFLIB_SPEC " %{fmudflap: -export-dynamic -lmudflap \
+ %{static:%(link_gcc_c_sequence) -lmudflap}} \
+ %{fmudflapth: -export-dynamic -lmudflapth -lpthread \
+ %{static:%(link_gcc_c_sequence) -lmudflapth}} "
+
+#undef TARGET_UNWIND_TABLES_DEFAULT
+#define TARGET_UNWIND_TABLES_DEFAULT true
