$NetBSD$

--- libgcc/config/i386/64/sfp-machine.h.orig	Mon Jun 22 14:04:19 2009
+++ libgcc/config/i386/64/sfp-machine.h
@@ -79,17 +79,25 @@ struct fenv
   unsigned short int __unused5;
 };
 
+#ifdef __AVX__
+ #define ASM_INVALID "vdivss %0, %0, %0"
+ #define ASM_DIVZERO "vdivss %1, %0, %0"
+#else
+ #define ASM_INVALID "divss %0, %0"
+ #define ASM_DIVZERO "divss %1, %0"
+#endif
+
 #define FP_HANDLE_EXCEPTIONS						\
   do {									\
     if (_fex & FP_EX_INVALID)						\
       {									\
 	float f = 0.0;							\
-	__asm__ __volatile__ ("divss %0, %0 " : : "x" (f));		\
+	__asm__ __volatile__ (ASM_INVALID : : "x" (f));			\
       }									\
     if (_fex & FP_EX_DIVZERO)						\
       {									\
 	float f = 1.0, g = 0.0;						\
-	__asm__ __volatile__ ("divss %1, %0" : : "x" (f), "x" (g));	\
+	__asm__ __volatile__ (ASM_DIVZERO : : "x" (f), "x" (g));	\
       }									\
     if (_fex & FP_EX_OVERFLOW)						\
       {									\
