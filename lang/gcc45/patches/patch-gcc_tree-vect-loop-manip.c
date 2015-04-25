$NetBSD$

--- gcc/tree-vect-loop-manip.c.orig	Tue Jan 19 16:05:57 2010
+++ gcc/tree-vect-loop-manip.c
@@ -1516,7 +1516,7 @@ vect_generate_tmps_on_preheader (loop_vec_info loop_vi
   edge pe;
   basic_block new_bb;
   gimple_seq stmts;
-  tree ni_name;
+  tree ni_name, ni_minus_gap_name;
   tree var;
   tree ratio_name;
   tree ratio_mult_vf_name;
@@ -1533,9 +1533,39 @@ vect_generate_tmps_on_preheader (loop_vec_info loop_vi
   ni_name = vect_build_loop_niters (loop_vinfo, cond_expr_stmt_list);
   log_vf = build_int_cst (TREE_TYPE (ni), exact_log2 (vf));
 
+  /* If epilogue loop is required because of data accesses with gaps, we
+     subtract one iteration from the total number of iterations here for
+     correct calculation of RATIO.  */
+  if (LOOP_VINFO_PEELING_FOR_GAPS (loop_vinfo))
+    {
+      ni_minus_gap_name = fold_build2 (MINUS_EXPR, TREE_TYPE (ni_name),
+				       ni_name,
+			               build_one_cst (TREE_TYPE (ni_name)));
+      if (!is_gimple_val (ni_minus_gap_name))
+	{
+	  var = create_tmp_var (TREE_TYPE (ni), "ni_gap");
+          add_referenced_var (var);
+
+          stmts = NULL;
+          ni_minus_gap_name = force_gimple_operand (ni_minus_gap_name, &stmts,
+						    true, var);
+          if (cond_expr_stmt_list)
+            gimple_seq_add_seq (&cond_expr_stmt_list, stmts);
+          else
+            {
+              pe = loop_preheader_edge (loop);
+              new_bb = gsi_insert_seq_on_edge_immediate (pe, stmts);
+              gcc_assert (!new_bb);
+            }
+        }
+    }
+  else
+    ni_minus_gap_name = ni_name;
+
   /* Create: ratio = ni >> log2(vf) */
 
-  ratio_name = fold_build2 (RSHIFT_EXPR, TREE_TYPE (ni_name), ni_name, log_vf);
+  ratio_name = fold_build2 (RSHIFT_EXPR, TREE_TYPE (ni_minus_gap_name),
+			    ni_minus_gap_name, log_vf);
   if (!is_gimple_val (ratio_name))
     {
       var = create_tmp_var (TREE_TYPE (ni), "bnd");
@@ -2312,26 +2342,26 @@ vect_create_cond_for_align_checks (loop_vec_info loop_
 
    Input:
      DR: The data reference.
-     VECT_FACTOR: vectorization factor.
+     LENGTH_FACTOR: segment length to consider.
 
    Return an expression whose value is the size of segment which will be
    accessed by DR.  */
 
 static tree
-vect_vfa_segment_size (struct data_reference *dr, tree vect_factor)
+vect_vfa_segment_size (struct data_reference *dr, tree length_factor)
 {
-  tree segment_length = fold_build2 (MULT_EXPR, integer_type_node,
-			             DR_STEP (dr), vect_factor);
-
+  tree segment_length;
+  segment_length = size_binop (MULT_EXPR,
+			       fold_convert (sizetype, DR_STEP (dr)),
+			       fold_convert (sizetype, length_factor));
   if (vect_supportable_dr_alignment (dr) == dr_explicit_realign_optimized)
     {
       tree vector_size = TYPE_SIZE_UNIT
 			  (STMT_VINFO_VECTYPE (vinfo_for_stmt (DR_STMT (dr))));
 
-      segment_length = fold_build2 (PLUS_EXPR, integer_type_node,
-				    segment_length, vector_size);
+      segment_length = size_binop (PLUS_EXPR, segment_length, vector_size);
     }
-  return fold_convert (sizetype, segment_length);
+  return segment_length;
 }
 
 
@@ -2365,12 +2395,12 @@ vect_create_cond_for_alias_checks (loop_vec_info loop_
   struct loop *loop = LOOP_VINFO_LOOP (loop_vinfo);
   VEC (ddr_p, heap) * may_alias_ddrs =
     LOOP_VINFO_MAY_ALIAS_DDRS (loop_vinfo);
-  tree vect_factor =
-    build_int_cst (integer_type_node, LOOP_VINFO_VECT_FACTOR (loop_vinfo));
+  int vect_factor = LOOP_VINFO_VECT_FACTOR (loop_vinfo);
+  tree scalar_loop_iters = LOOP_VINFO_NITERS (loop_vinfo);
 
   ddr_p ddr;
   unsigned int i;
-  tree part_cond_expr;
+  tree part_cond_expr, length_factor;
 
   /* Create expression
      ((store_ptr_0 + store_segment_length_0) < load_ptr_0)
@@ -2417,8 +2447,12 @@ vect_create_cond_for_alias_checks (loop_vec_info loop_
         vect_create_addr_base_for_vector_ref (stmt_b, cond_expr_stmt_list,
 					      NULL_TREE, loop);
 
-      segment_length_a = vect_vfa_segment_size (dr_a, vect_factor);
-      segment_length_b = vect_vfa_segment_size (dr_b, vect_factor);
+      if (!operand_equal_p (DR_STEP (dr_a), DR_STEP (dr_b), 0))
+	length_factor = scalar_loop_iters;
+      else
+	length_factor = size_int (vect_factor);
+      segment_length_a = vect_vfa_segment_size (dr_a, length_factor);
+      segment_length_b = vect_vfa_segment_size (dr_b, length_factor);
 
       if (vect_print_dump_info (REPORT_DR_DETAILS))
 	{
