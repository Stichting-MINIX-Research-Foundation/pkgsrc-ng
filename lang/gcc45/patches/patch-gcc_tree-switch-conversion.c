$NetBSD$

--- gcc/tree-switch-conversion.c.orig	Thu Sep  2 13:05:30 2010
+++ gcc/tree-switch-conversion.c
@@ -549,7 +549,7 @@ static void
 build_arrays (gimple swtch)
 {
   tree arr_index_type;
-  tree tidx, sub, tmp;
+  tree tidx, sub, tmp, utype;
   gimple stmt;
   gimple_stmt_iterator gsi;
   int i;
@@ -557,14 +557,20 @@ build_arrays (gimple swtch)
 
   gsi = gsi_for_stmt (swtch);
 
+  /* Make sure we do not generate arithmetics in a subrange.  */
+  utype = TREE_TYPE (info.index_expr);
+  if (TREE_TYPE (utype))
+    utype = lang_hooks.types.type_for_mode (TYPE_MODE (TREE_TYPE (utype)), 1);
+  else
+    utype = lang_hooks.types.type_for_mode (TYPE_MODE (utype), 1);
+
   arr_index_type = build_index_type (info.range_size);
-  tmp = create_tmp_var (TREE_TYPE (info.index_expr), "csti");
+  tmp = create_tmp_var (utype, "csui");
   add_referenced_var (tmp);
   tidx = make_ssa_name (tmp, NULL);
-  sub = fold_build2_loc (loc, MINUS_EXPR,
-		     TREE_TYPE (info.index_expr), info.index_expr,
-		     fold_convert_loc (loc, TREE_TYPE (info.index_expr),
-				       info.range_min));
+  sub = fold_build2_loc (loc, MINUS_EXPR, utype,
+			 fold_convert_loc (loc, utype, info.index_expr),
+			 fold_convert_loc (loc, utype, info.range_min));
   sub = force_gimple_operand_gsi (&gsi, sub,
 				  false, NULL, true, GSI_SAME_STMT);
   stmt = gimple_build_assign (tidx, sub);
@@ -673,12 +679,7 @@ gen_inbound_check (gimple swtch)
   tree label_decl2 = create_artificial_label (UNKNOWN_LOCATION);
   tree label_decl3 = create_artificial_label (UNKNOWN_LOCATION);
   gimple label1, label2, label3;
-
-  tree utype;
-  tree tmp_u_1, tmp_u_2, tmp_u_var;
-  tree cast;
-  gimple cast_assign, minus_assign;
-  tree ulb, minus;
+  tree utype, tidx;
   tree bound;
 
   gimple cond_stmt;
@@ -692,49 +693,24 @@ gen_inbound_check (gimple swtch)
   gcc_assert (info.default_values);
   bb0 = gimple_bb (swtch);
 
-  /* Make sure we do not generate arithmetics in a subrange.  */
-  if (TREE_TYPE (TREE_TYPE (info.index_expr)))
-    utype = lang_hooks.types.type_for_mode
-      (TYPE_MODE (TREE_TYPE (TREE_TYPE (info.index_expr))), 1);
-  else
-    utype = lang_hooks.types.type_for_mode
-      (TYPE_MODE (TREE_TYPE (info.index_expr)), 1);
+  tidx = gimple_assign_lhs (info.arr_ref_first);
+  utype = TREE_TYPE (tidx);
 
   /* (end of) block 0 */
   gsi = gsi_for_stmt (info.arr_ref_first);
-  tmp_u_var = create_tmp_var (utype, "csui");
-  add_referenced_var (tmp_u_var);
-  tmp_u_1 = make_ssa_name (tmp_u_var, NULL);
+  gsi_next (&gsi);
 
-  cast = fold_convert_loc (loc, utype, info.index_expr);
-  cast_assign = gimple_build_assign (tmp_u_1, cast);
-  SSA_NAME_DEF_STMT (tmp_u_1) = cast_assign;
-  gsi_insert_before (&gsi, cast_assign, GSI_SAME_STMT);
-  update_stmt (cast_assign);
-
-  ulb = fold_convert_loc (loc, utype, info.range_min);
-  minus = fold_build2_loc (loc, MINUS_EXPR, utype, tmp_u_1, ulb);
-  minus = force_gimple_operand_gsi (&gsi, minus, false, NULL, true,
-				    GSI_SAME_STMT);
-  tmp_u_2 = make_ssa_name (tmp_u_var, NULL);
-  minus_assign = gimple_build_assign (tmp_u_2, minus);
-  SSA_NAME_DEF_STMT (tmp_u_2) = minus_assign;
-  gsi_insert_before (&gsi, minus_assign, GSI_SAME_STMT);
-  update_stmt (minus_assign);
-
   bound = fold_convert_loc (loc, utype, info.range_size);
-  cond_stmt = gimple_build_cond (LE_EXPR, tmp_u_2, bound, NULL_TREE, NULL_TREE);
+  cond_stmt = gimple_build_cond (LE_EXPR, tidx, bound, NULL_TREE, NULL_TREE);
   gsi_insert_before (&gsi, cond_stmt, GSI_SAME_STMT);
   update_stmt (cond_stmt);
 
   /* block 2 */
-  gsi = gsi_for_stmt (info.arr_ref_first);
   label2 = gimple_build_label (label_decl2);
   gsi_insert_before (&gsi, label2, GSI_SAME_STMT);
   last_assign = gen_def_assigns (&gsi);
 
   /* block 1 */
-  gsi = gsi_for_stmt (info.arr_ref_first);
   label1 = gimple_build_label (label_decl1);
   gsi_insert_before (&gsi, label1, GSI_SAME_STMT);
 
