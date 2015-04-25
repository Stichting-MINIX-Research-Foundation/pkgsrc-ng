$NetBSD$

--- gcc/tree-cfgcleanup.c.orig	Fri May 21 09:27:30 2010
+++ gcc/tree-cfgcleanup.c
@@ -560,7 +560,7 @@ split_bbs_on_noreturn_calls (void)
 	   BB is present in the cfg.  */
 	if (bb == NULL
 	    || bb->index < NUM_FIXED_BLOCKS
-	    || bb->index >= n_basic_blocks
+	    || bb->index >= last_basic_block
 	    || BASIC_BLOCK (bb->index) != bb
 	    || last_stmt (bb) == stmt
 	    || !gimple_call_noreturn_p (stmt))
