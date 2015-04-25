$NetBSD$

--- gcc/config/rs6000/netbsd.h.orig	Fri Feb 20 15:20:38 2009
+++ gcc/config/rs6000/netbsd.h
@@ -19,6 +19,22 @@
    along with GCC; see the file COPYING3.  If not see
    <http://www.gnu.org/licenses/>.  */
 
+/* This defines which switch letters take arguments.  On NetBSD, most
+   of the normal cases (defined by gcc.c) apply, and we also have -h*
+   and -z* options (for the linker) (coming from SVR4).
+   Copied from ../netbsd-elf.h and re{undef,defined} here to
+   override the powerpc sysv4.h definition.
+   netbsd-elf.h defines the default list + 'h' + 'z' + 'R'.
+   rs6000/sysv4.h defines the default list + 'G'. */
+
+#undef SWITCH_TAKES_ARG
+#define SWITCH_TAKES_ARG(CHAR)			\
+  (DEFAULT_SWITCH_TAKES_ARG (CHAR)		\
+   || (CHAR) == 'h'				\
+   || (CHAR) == 'z'				\
+   || (CHAR) == 'R'				\
+   || (CHAR) == 'G')
+
 #undef  TARGET_OS_CPP_BUILTINS	/* FIXME: sysv4.h should not define this! */
 #define TARGET_OS_CPP_BUILTINS()		\
   do						\
@@ -27,6 +43,10 @@
       builtin_define ("__powerpc__");		\
       builtin_assert ("cpu=powerpc");		\
       builtin_assert ("machine=powerpc");	\
+      if (TARGET_SECURE_PLT)			\
+        builtin_define ("_SECURE_PLT");		\
+      if (TARGET_SOFT_FLOAT)			\
+        builtin_define ("_SOFT_FLOAT");		\
     }						\
   while (0)
 
@@ -58,6 +78,17 @@
 #undef  PTRDIFF_TYPE
 #define PTRDIFF_TYPE "int"
 
+/* Redefine some types that where redefined by rs6000 include files.  */
+
+#undef WCHAR_TYPE
+#define WCHAR_TYPE "int"
+
+#undef WCHAR_TYPE_SIZE
+#define WCHAR_TYPE_SIZE 32
+
+#undef WINT_TYPE
+#define WINT_TYPE "int"
+
 /* Undo the spec mess from sysv4.h, and just define the specs
    the way NetBSD systems actually expect.  */
 
@@ -82,10 +113,41 @@
 
 #undef  SUBTARGET_EXTRA_SPECS
 #define SUBTARGET_EXTRA_SPECS					\
+  { "cc1_secure_plt_default",	CC1_SECURE_PLT_DEFAULT_SPEC },	\
   { "netbsd_link_spec",		NETBSD_LINK_SPEC_ELF },		\
   { "netbsd_entry_point",	NETBSD_ENTRY_POINT },		\
   { "netbsd_endfile_spec",	NETBSD_ENDFILE_SPEC },
 
+/*
+ * Add NetBSD specific defaults: -mpowerpc -mnew_mnemonics -mstrict-align
+ */
+#undef TARGET_DEFAULT
+#define TARGET_DEFAULT (MASK_POWERPC | MASK_NEW_MNEMONICS | MASK_STRICT_ALIGN)
+
+/*
+ * We know we have the right binutils for this (we shouldn't need to do this
+ * but until the cross build does the right thing...)
+ */
+#undef TARGET_SECURE_PLT
+#define TARGET_SECURE_PLT secure_plt
+#undef HAVE_AS_TLS
+#define HAVE_AS_TLS 1
+
+/* Attempt to enable execute permissions on the stack.  */
+#define TRANSFER_FROM_TRAMPOLINE NETBSD_ENABLE_EXECUTE_STACK
+#ifdef L_trampoline
+#undef TRAMPOLINE_SIZE
+#define TRAMPOLINE_SIZE 48
+#endif
+
+/* Make sure _enable_execute_stack() isn't the empty function in libgcc2.c.
+   It gets defined in _trampoline.o via NETBSD_ENABLE_EXECUTE_STACK.  */
+#undef ENABLE_EXECUTE_STACK
+#define ENABLE_EXECUTE_STACK
+
+/* Override STACK_BOUNDARY to use Altivec compliant one.  */
+#undef STACK_BOUNDARY
+#define STACK_BOUNDARY	128
 
 #undef  TARGET_VERSION
 #define TARGET_VERSION fprintf (stderr, " (NetBSD/powerpc ELF)");
