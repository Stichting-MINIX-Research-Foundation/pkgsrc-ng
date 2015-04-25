$NetBSD$

--- gcc/tree-outof-ssa.c.orig	Fri Apr  2 19:54:46 2010
+++ gcc/tree-outof-ssa.c
@@ -233,9 +233,10 @@ insert_value_copy_on_edge (edge e, int dest, tree src,
 
   var = SSA_NAME_VAR (partition_to_var (SA.map, dest));
   src_mode = TYPE_MODE (TREE_TYPE (src));
-  dest_mode = promote_decl_mode (var, &unsignedp);
+  dest_mode = GET_MODE (SA.partition_to_pseudo[dest]);
   gcc_assert (src_mode == TYPE_MODE (TREE_TYPE (var)));
-  gcc_assert (dest_mode == GET_MODE (SA.partition_to_pseudo[dest]));
+  gcc_assert (!REG_P (SA.partition_to_pseudo[dest])
+	      || dest_mode == promote_decl_mode (var, &unsignedp));
 
   if (src_mode != dest_mode)
     {
