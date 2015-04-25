$NetBSD$

--- gcc/config/i386/darwin.h.orig	Fri Sep 10 16:12:46 2010
+++ gcc/config/i386/darwin.h
@@ -302,3 +302,17 @@ along with GCC; see the file COPYING3.  If not see
 #define MACHO_SYMBOL_FLAG_VARIABLE ((SYMBOL_FLAG_MACH_DEP) << 3)
 
 #define SUBTARGET32_DEFAULT_CPU "i686"
+
+#define SUBTARGET_INIT_BUILTINS					\
+do {								\
+  darwin_rename_builtins ();					\
+} while(0)
+ 
+/* The system ___divdc3 routine in libSystem on darwin10 is not
+   accurate to 1ulp, ours is, so we avoid ever using the system name
+   for this routine and instead install a non-conflicting name that is
+   accurate.  See darwin_rename_builtins.  */
+#ifdef L_divdc3
+#define DECLARE_LIBRARY_RENAMES \
+  asm(".text; ___divdc3: jmp ___ieee_divdc3 ; .globl ___divdc3");
+#endif
