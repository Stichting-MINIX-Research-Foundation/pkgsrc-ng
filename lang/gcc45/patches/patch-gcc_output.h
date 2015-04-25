$NetBSD$

--- gcc/output.h.orig	Mon Oct 26 21:57:10 2009
+++ gcc/output.h
@@ -115,7 +115,7 @@ extern void output_addr_const (FILE *, rtx);
 
 /* Output a string of assembler code, substituting numbers, strings
    and fixed syntactic prefixes.  */
-#if GCC_VERSION >= 3004
+#if GCC_VERSION >= 3004 && !defined(__clang__)
 #define ATTRIBUTE_ASM_FPRINTF(m, n) __attribute__ ((__format__ (__asm_fprintf__, m, n))) ATTRIBUTE_NONNULL(m)
 /* This is a magic identifier which allows GCC to figure out the type
    of HOST_WIDE_INT for %wd specifier checks.  You must issue this
