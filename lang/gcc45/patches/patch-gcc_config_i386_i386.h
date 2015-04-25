$NetBSD$

--- gcc/config/i386/i386.h.orig	Wed Mar 30 10:48:07 2011
+++ gcc/config/i386/i386.h
@@ -397,7 +397,7 @@ extern unsigned char ix86_tune_features[X86_TUNE_LAST]
 
 /* Feature tests against the various architecture variations.  */
 enum ix86_arch_indices {
-  X86_ARCH_CMOVE,		/* || TARGET_SSE */
+  X86_ARCH_CMOV,
   X86_ARCH_CMPXCHG,
   X86_ARCH_CMPXCHG8B,
   X86_ARCH_XADD,
@@ -408,12 +408,16 @@ enum ix86_arch_indices {
 
 extern unsigned char ix86_arch_features[X86_ARCH_LAST];
 
-#define TARGET_CMOVE		ix86_arch_features[X86_ARCH_CMOVE]
+#define TARGET_CMOV		ix86_arch_features[X86_ARCH_CMOV]
 #define TARGET_CMPXCHG		ix86_arch_features[X86_ARCH_CMPXCHG]
 #define TARGET_CMPXCHG8B	ix86_arch_features[X86_ARCH_CMPXCHG8B]
 #define TARGET_XADD		ix86_arch_features[X86_ARCH_XADD]
 #define TARGET_BSWAP		ix86_arch_features[X86_ARCH_BSWAP]
 
+/* For sane SSE instruction set generation we need fcomi instruction.
+   It is safe to enable all CMOVE instructions.  */
+#define TARGET_CMOVE		(TARGET_CMOV || TARGET_SSE)
+
 #define TARGET_FISTTP		(TARGET_SSE3 && TARGET_80387)
 
 extern int x86_prefetch_sse;
@@ -1081,6 +1085,7 @@ enum target_cpu_default
 
 #define HARD_REGNO_CALLER_SAVE_MODE(REGNO, NREGS, MODE)			\
   (CC_REGNO_P (REGNO) ? VOIDmode					\
+   : MMX_REGNO_P (REGNO) ? V8QImode					\
    : (MODE) == VOIDmode && (NREGS) != 1 ? VOIDmode			\
    : (MODE) == VOIDmode ? choose_hard_reg_mode ((REGNO), (NREGS), false) \
    : (MODE) == HImode && !TARGET_PARTIAL_REG_STALL ? SImode		\
@@ -1765,6 +1770,17 @@ typedef struct ix86_args {
    It is given that X satisfies CONSTANT_P or is a CONST_DOUBLE.  */
 
 #define LEGITIMATE_CONSTANT_P(X)  legitimate_constant_p (X)
+
+/* Try a machine-dependent way of reloading an illegitimate address
+   operand.  If we find one, push the reload and jump to WIN.  This
+   macro is used in only one place: `find_reloads_address' in reload.c.  */
+
+#define LEGITIMIZE_RELOAD_ADDRESS(X, MODE, OPNUM, TYPE, INDL, WIN)	\
+do {									\
+  if (ix86_legitimize_reload_address ((X), (MODE), (OPNUM),		\
+				      (int)(TYPE), (INDL)))		\
+    goto WIN;								\
+} while (0)
 
 /* If defined, a C expression to determine the base term of address X.
    This macro is used in only one place: `find_base_term' in alias.c.
