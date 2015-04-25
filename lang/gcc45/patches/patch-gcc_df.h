$NetBSD$

--- gcc/df.h.orig	Fri Jan 29 12:14:47 2010
+++ gcc/df.h
@@ -51,7 +51,7 @@ union df_ref_d;
 #define DF_RD      3      /* Reaching Defs. */
 #define DF_CHAIN   4      /* Def-Use and/or Use-Def Chains. */
 #define DF_BYTE_LR 5      /* Subreg tracking lr.  */
-#define DF_NOTE    6      /* REG_DEF and REG_UNUSED notes. */
+#define DF_NOTE    6      /* REG_DEAD and REG_UNUSED notes. */
 #define DF_MD      7      /* Multiple Definitions. */
 
 #define DF_LAST_PROBLEM_PLUS1 (DF_MD + 1)
@@ -978,6 +978,7 @@ extern void df_note_add_problem (void);
 extern void df_md_add_problem (void);
 extern void df_md_simulate_artificial_defs_at_top (basic_block, bitmap);
 extern void df_md_simulate_one_insn (basic_block, rtx, bitmap);
+extern void df_simulate_find_noclobber_defs (rtx, bitmap);
 extern void df_simulate_find_defs (rtx, bitmap);
 extern void df_simulate_defs (rtx, bitmap);
 extern void df_simulate_uses (rtx, bitmap);
