$NetBSD$

--- gcc/config/pa/pa-protos.h.orig	Wed Sep 23 19:08:32 2009
+++ gcc/config/pa/pa-protos.h
@@ -79,7 +79,6 @@ extern int move_src_operand (rtx, enum machine_mode);
 extern int prefetch_cc_operand (rtx, enum machine_mode);
 extern int prefetch_nocc_operand (rtx, enum machine_mode);
 extern int and_operand (rtx, enum machine_mode);
-extern int ior_operand (rtx, enum machine_mode);
 extern int arith32_operand (rtx, enum machine_mode);
 extern int uint32_operand (rtx, enum machine_mode);
 extern int reg_before_reload_operand (rtx, enum machine_mode);
@@ -94,7 +93,6 @@ extern int ireg_or_int5_operand (rtx, enum machine_mod
 extern int fmpyaddoperands (rtx *);
 extern int fmpysuboperands (rtx *);
 extern int call_operand_address (rtx, enum machine_mode);
-extern int ior_operand (rtx, enum machine_mode);
 extern void emit_bcond_fp (rtx[]);
 extern int emit_move_sequence (rtx *, enum machine_mode, rtx);
 extern int emit_hpdiv_const (rtx *, int);
