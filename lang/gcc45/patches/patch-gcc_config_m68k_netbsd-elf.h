$NetBSD$

--- gcc/config/m68k/netbsd-elf.h.orig	Tue Sep 22 15:49:54 2009
+++ gcc/config/m68k/netbsd-elf.h
@@ -35,28 +35,39 @@ along with GCC; see the file COPYING3.  If not see
     }						\
   while (0)
 
-/* Don't try using XFmode on the 68010.  */ 
+/* Don't try using XFmode on the 68010 or coldfire.  */ 
 #undef LONG_DOUBLE_TYPE_SIZE
 #define LONG_DOUBLE_TYPE_SIZE (TARGET_68020 ? 80 : 64)
 
 #undef LIBGCC2_LONG_DOUBLE_TYPE_SIZE
-#ifdef __mc68010__
+#if defined(__mc68010__) || defined(__mcoldfire__)
 #define LIBGCC2_LONG_DOUBLE_TYPE_SIZE 64
 #else
 #define LIBGCC2_LONG_DOUBLE_TYPE_SIZE 80
 #endif
 
+#undef SUBTARGET_OVERRIDE_OPTIONS
+#define SUBTARGET_OVERRIDE_OPTIONS \
+  { \
+    if (TARGET_COLDFIRE) \
+      { \
+	target_flags |= MASK_STRICT_ALIGNMENT | MASK_CF_HWDIV; \
+	if ((target_flags_explicit & MASK_HARD_FLOAT) == 0) \
+	  { \
+	    target_flags &= ~MASK_HARD_FLOAT; \
+	    m68k_fpu = FPUTYPE_NONE; \
+	  } \
+      } \
+  }
+
 #undef SUBTARGET_EXTRA_SPECS
 #define SUBTARGET_EXTRA_SPECS \
+  { "netbsd_cpp_spec",      NETBSD_CPP_SPEC }, \
   { "netbsd_entry_point",   NETBSD_ENTRY_POINT },
 
 
 #undef TARGET_VERSION
-#define TARGET_VERSION			\
-  fprintf (stderr,			\
-	   TARGET_68010			\
-	   ? " (NetBSD/68010 ELF)"	\
-	   : " (NetBSD/m68k ELF)");
+#define TARGET_VERSION fprintf (stderr, " (NetBSD/m68k ELF)");
 
 
 /* Provide a CPP_SPEC appropriate for NetBSD m68k targets.  Currently we
@@ -64,14 +75,20 @@ along with GCC; see the file COPYING3.  If not see
    whether or not use of the FPU is allowed.  */
 
 #undef CPP_SPEC
-#define CPP_SPEC NETBSD_CPP_SPEC
+#define CPP_SPEC \
+  "%(netbsd_cpp_spec)"
 
 
 /* Provide an ASM_SPEC appropriate for NetBSD m68k ELF targets.  We need
    to pass PIC code generation options.  */
 
 #undef ASM_SPEC
-#define ASM_SPEC "%(asm_cpu_spec) %{fpic|fpie:-k} %{fPIC|fPIE:-k -K}"
+#define ASM_SPEC \
+  "%(asm_default_spec) \
+    %{m68010} %{m68020} %{m68030} %{m68040} %{m68060} \
+    %{m5200} %{m5206e} %{m528x} %{m5307} %{m5407} %{mcfv4e}\
+    %{mcpu=*:-mcpu=%*} %{march=*:-march=%*}\
+    %{fpic|fpie:-k} %{fPIC|fPIE:-k -K}"
 
 #define AS_NEEDS_DASH_FOR_PIPED_INPUT
 
@@ -80,6 +97,11 @@ along with GCC; see the file COPYING3.  If not see
 #undef LINK_SPEC
 #define LINK_SPEC NETBSD_LINK_SPEC_ELF
 
+/* NetBSD/sun2 does not support shlibs, avoid using libgcc_pic.  */
+#if TARGET_DEFAULT_CPU == 0
+#undef REAL_LIBGCC_SPEC
+#endif
+
 #define NETBSD_ENTRY_POINT "_start"
 
 /* Output assembler code to FILE to increment profiler label # LABELNO
@@ -89,7 +111,13 @@ along with GCC; see the file COPYING3.  If not see
 #define FUNCTION_PROFILER(FILE, LABELNO)				\
 do									\
   {									\
-    asm_fprintf (FILE, "\tlea (%LLP%d,%Rpc),%Ra1\n", (LABELNO));	\
+    if (TARGET_COLDFIRE)						\
+      {									\
+        asm_fprintf (FILE, "\tmovea.l #%LLP%d-.,%Ra1\n", (LABELNO));	\
+        asm_fprintf (FILE, "\tlea (-6,%Rpc,%Ra1),%Ra1\n", (LABELNO));	\
+      }									\
+    else								\
+      asm_fprintf (FILE, "\tlea (%LLP%d,%Rpc),%Ra1\n", (LABELNO));	\
     if (flag_pic)							\
       fprintf (FILE, "\tbsr.l __mcount@PLTPC\n");			\
     else								\
@@ -289,6 +317,8 @@ while (0)
 
 #undef STACK_BOUNDARY
 #define STACK_BOUNDARY 32
+#undef PREFERRED_STACK_BOUNDARY
+#define PREFERRED_STACK_BOUNDARY 32
 
 
 /* Alignment of field after `int : 0' in a structure.
