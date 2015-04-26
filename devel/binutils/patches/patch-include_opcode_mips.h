$NetBSD$

--- include/opcode/mips.h.orig	Tue Sep  4 14:21:05 2012
+++ include/opcode/mips.h
@@ -1035,7 +1035,11 @@ enum
   M_DSUB_I,
   M_DSUBU_I,
   M_DSUBU_I_2,
+  M_JR_S,
+  M_J_S,
   M_J_A,
+  M_JALR_S,
+  M_JALR_DS,
   M_JAL_1,
   M_JAL_2,
   M_JAL_A,
