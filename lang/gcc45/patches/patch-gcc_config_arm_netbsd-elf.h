$NetBSD$

--- gcc/config/arm/netbsd-elf.h.orig	Thu Nov  5 14:47:45 2009
+++ gcc/config/arm/netbsd-elf.h
@@ -24,6 +24,14 @@
 
 /* arm.h defaults to ARM6 CPU.  */
 
+/* Default EABI to armv5t so that thumb shared libraries work.
+   The ARM926EH-S core is the default for armv5te, so set
+   SUBTARGET_CPU_DEFAULT to achieve this.  */
+
+#define SUBTARGET_CPU_DEFAULT \
+	(ARM_DEFAULT_ABI != ARM_ABI_APCS && ARM_DEFAULT_ABI != ARM_ABI_ATPCS \
+	    ? TARGET_CPU_arm926ejs : TARGET_CPU_arm6)
+
 /* This defaults us to little-endian.  */
 #ifndef TARGET_ENDIAN_DEFAULT
 #define TARGET_ENDIAN_DEFAULT 0
@@ -40,6 +48,7 @@
 #undef ARM_DEFAULT_ABI
 #define ARM_DEFAULT_ABI ARM_ABI_ATPCS
 
+#undef TARGET_OS_CPP_BUILTINS
 #define TARGET_OS_CPP_BUILTINS()	\
   do					\
     {					\
@@ -52,13 +61,13 @@
 
 #undef SUBTARGET_EXTRA_ASM_SPEC
 #define SUBTARGET_EXTRA_ASM_SPEC	\
-  "-matpcs %{fpic|fpie:-k} %{fPIC|fPIE:-k}"
+  "-matpcs %{mabi=aapcs*:-meabi=5} %{fpic|fpie:-k} %{fPIC|fPIE:-k}"
 
 /* Default to full VFP if -mhard-float is specified.  */
 #undef SUBTARGET_ASM_FLOAT_SPEC
 #define SUBTARGET_ASM_FLOAT_SPEC	\
-  "%{mhard-float:{!mfpu=*:-mfpu=vfp}}   \
-   %{mfloat-abi=hard:{!mfpu=*:-mfpu=vfp}}"
+  "%{mhard-float:%{!mfpu=*:-mfpu=vfp}}   \
+   %{mfloat-abi=hard:%{!mfpu=*:-mfpu=vfp}}"
 
 #undef SUBTARGET_EXTRA_SPECS
 #define SUBTARGET_EXTRA_SPECS				\
@@ -71,7 +80,9 @@
 
 #undef LINK_SPEC
 #define LINK_SPEC \
-  "-X %{mbig-endian:-EB} %{mlittle-endian:-EL} \
+  "-X \
+   %{mbig-endian:-EB %{-mabi=aapcs*:-m armelfb_nbsd_eabi}} \
+   %{mlittle-endian:-EL %{-mabi=aapcs*:-m armelf_nbsd_eabi}} \
    %(netbsd_link_spec)"
 
 /* Make GCC agree with <machine/ansi.h>.  */
