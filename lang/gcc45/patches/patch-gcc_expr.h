$NetBSD$

--- gcc/expr.h.orig	Fri Feb 19 09:53:51 2010
+++ gcc/expr.h
@@ -460,6 +460,8 @@ extern void emit_group_store (rtx, rtx, tree, int);
 /* Copy BLKmode object from a set of registers.  */
 extern rtx copy_blkmode_from_reg (rtx, rtx, tree);
 
+extern rtx copy_blkmode_to_reg (enum machine_mode, tree);
+
 /* Mark REG as holding a parameter for the next CALL_INSN.  */
 extern void use_reg (rtx *, rtx);
 
