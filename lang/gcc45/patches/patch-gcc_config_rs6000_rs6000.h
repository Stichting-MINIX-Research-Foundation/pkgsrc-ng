$NetBSD$

--- gcc/config/rs6000/rs6000.h.orig	Mon Mar  7 19:40:15 2011
+++ gcc/config/rs6000/rs6000.h
@@ -1038,10 +1038,9 @@ extern unsigned rs6000_pointer_size;
 
 /* When setting up caller-save slots (MODE == VOIDmode) ensure we allocate
    enough space to account for vectors in FP regs. */
-#define HARD_REGNO_CALLER_SAVE_MODE(REGNO, NREGS, MODE)	\
-  (TARGET_VSX						\
-   && ((MODE) == VOIDmode || VSX_VECTOR_MODE (MODE)	\
-       || ALTIVEC_VECTOR_MODE (MODE))			\
+#define HARD_REGNO_CALLER_SAVE_MODE(REGNO, NREGS, MODE)			\
+  (TARGET_VSX								\
+   && ((MODE) == VOIDmode || ALTIVEC_OR_VSX_VECTOR_MODE (MODE))		\
    && FP_REGNO_P (REGNO)				\
    ? V2DFmode						\
    : choose_hard_reg_mode ((REGNO), (NREGS), false))
@@ -1057,25 +1056,16 @@ extern unsigned rs6000_pointer_size;
 	 ((MODE) == V4SFmode		\
 	  || (MODE) == V2DFmode)	\
 
-#define VSX_SCALAR_MODE(MODE)		\
-	((MODE) == DFmode)
-
-#define VSX_MODE(MODE)			\
-	(VSX_VECTOR_MODE (MODE)		\
-	 || VSX_SCALAR_MODE (MODE))
-
-#define VSX_MOVE_MODE(MODE)		\
-	(VSX_VECTOR_MODE (MODE)		\
-	 || VSX_SCALAR_MODE (MODE)	\
-	 || ALTIVEC_VECTOR_MODE (MODE)	\
-	 || (MODE) == TImode)
-
 #define ALTIVEC_VECTOR_MODE(MODE)	\
 	 ((MODE) == V16QImode		\
 	  || (MODE) == V8HImode		\
 	  || (MODE) == V4SFmode		\
 	  || (MODE) == V4SImode)
 
+#define ALTIVEC_OR_VSX_VECTOR_MODE(MODE)				\
+  (ALTIVEC_VECTOR_MODE (MODE) || VSX_VECTOR_MODE (MODE)			\
+   || (MODE) == V2DImode)
+
 #define SPE_VECTOR_MODE(MODE)		\
 	((MODE) == V4HImode          	\
          || (MODE) == V2SFmode          \
@@ -1118,10 +1108,10 @@ extern unsigned rs6000_pointer_size;
    ? ALTIVEC_VECTOR_MODE (MODE2)		\
    : ALTIVEC_VECTOR_MODE (MODE2)		\
    ? ALTIVEC_VECTOR_MODE (MODE1)		\
-   : VSX_VECTOR_MODE (MODE1)			\
-   ? VSX_VECTOR_MODE (MODE2)			\
-   : VSX_VECTOR_MODE (MODE2)			\
-   ? VSX_VECTOR_MODE (MODE1)			\
+   : ALTIVEC_OR_VSX_VECTOR_MODE (MODE1)		\
+   ? ALTIVEC_OR_VSX_VECTOR_MODE (MODE2)		\
+   : ALTIVEC_OR_VSX_VECTOR_MODE (MODE2)		\
+   ? ALTIVEC_OR_VSX_VECTOR_MODE (MODE1)		\
    : 1)
 
 /* Post-reload, we can't use any new AltiVec registers, as we already
