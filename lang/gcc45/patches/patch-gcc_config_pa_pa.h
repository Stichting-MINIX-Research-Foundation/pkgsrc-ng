$NetBSD$

--- gcc/config/pa/pa.h.orig	Sat Apr 16 17:10:29 2011
+++ gcc/config/pa/pa.h
@@ -891,6 +891,9 @@ extern int may_call_alloca;
    && (NEW_HP_ASSEMBLER						\
        || TARGET_GAS						\
        || GET_CODE (X) != LABEL_REF)				\
+   && (!PA_SYMBOL_REF_TLS_P (X)					\
+       || (SYMBOL_REF_TLS_MODEL (X) != TLS_MODEL_GLOBAL_DYNAMIC		\
+	   && SYMBOL_REF_TLS_MODEL (X) != TLS_MODEL_LOCAL_DYNAMIC))	\
    && (!TARGET_64BIT						\
        || GET_CODE (X) != CONST_DOUBLE)				\
    && (!TARGET_64BIT						\
@@ -1196,7 +1199,7 @@ extern int may_call_alloca;
    There may be more opportunities to improve code with this hook.  */
 #define LEGITIMIZE_RELOAD_ADDRESS(AD, MODE, OPNUM, TYPE, IND, WIN) 	\
 do { 									\
-  long offset, newoffset, mask;						\
+  HOST_WIDE_INT offset, newoffset, mask;						\
   rtx new_rtx, temp = NULL_RTX;						\
 									\
   mask = (GET_MODE_CLASS (MODE) == MODE_FLOAT				\
