$NetBSD$

--- gcc/fwprop.c.orig	Fri Apr  2 19:54:46 2010
+++ gcc/fwprop.c
@@ -228,7 +228,10 @@ single_def_use_enter_block (struct dom_walk_data *walk
 
   process_uses (df_get_artificial_uses (bb_index), DF_REF_AT_TOP);
   process_defs (df_get_artificial_defs (bb_index), DF_REF_AT_TOP);
-  df_simulate_initialize_forwards (bb, local_lr);
+
+  /* We don't call df_simulate_initialize_forwards, as it may overestimate
+     the live registers if there are unused artificial defs.  We prefer
+     liveness to be underestimated.  */
 
   FOR_BB_INSNS (bb, insn)
     if (INSN_P (insn))
