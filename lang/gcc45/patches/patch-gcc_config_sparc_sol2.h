$NetBSD$

--- gcc/config/sparc/sol2.h.orig	Sat Nov 20 22:05:08 2010
+++ gcc/config/sparc/sol2.h
@@ -153,11 +153,18 @@ along with GCC; see the file COPYING3.  If not see
 #undef SUN_INTEGER_MULTIPLY_64
 #define SUN_INTEGER_MULTIPLY_64 1
 
-/* Solaris allows 64 bit out and global registers in 32 bit mode.
-   sparc_override_options will disable V8+ if not generating V9 code.  */
+/* Solaris allows 64-bit out and global registers to be used in 32-bit mode.
+   sparc_override_options will disable V8+ if either not generating V9 code
+   or generating 64-bit code.  */
 #undef TARGET_DEFAULT
-#define TARGET_DEFAULT (MASK_V8PLUS + MASK_APP_REGS + MASK_FPU \
-			+ MASK_LONG_DOUBLE_128)
+#ifdef TARGET_64BIT_DEFAULT
+#define TARGET_DEFAULT \
+  (MASK_V9 + MASK_64BIT + MASK_PTR64 + MASK_STACK_BIAS + \
+   MASK_V8PLUS + MASK_APP_REGS + MASK_FPU + MASK_LONG_DOUBLE_128)
+#else
+#define TARGET_DEFAULT \
+  (MASK_V8PLUS + MASK_APP_REGS + MASK_FPU + MASK_LONG_DOUBLE_128)
+#endif
 
 /* Solaris-specific #pragmas are implemented on top of attributes.  Hook in
    the bits from config/sol2.c.  */
