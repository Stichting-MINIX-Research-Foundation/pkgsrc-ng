$NetBSD$

--- gcc/config/i386/i386-protos.h.orig	Thu Jul 22 06:42:02 2010
+++ gcc/config/i386/i386-protos.h
@@ -57,7 +57,8 @@ extern bool legitimate_constant_p (rtx);
 extern bool constant_address_p (rtx);
 extern bool legitimate_pic_operand_p (rtx);
 extern int legitimate_pic_address_disp_p (rtx);
-
+extern bool ix86_legitimize_reload_address (rtx, enum machine_mode,
+					    int, int, int);
 extern void print_reg (rtx, int, FILE*);
 extern void print_operand (FILE*, rtx, int);
 extern void print_operand_address (FILE*, rtx);
