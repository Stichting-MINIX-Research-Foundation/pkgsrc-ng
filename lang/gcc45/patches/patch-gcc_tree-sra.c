$NetBSD$

--- gcc/tree-sra.c.orig	Tue Dec 21 11:05:49 2010
+++ gcc/tree-sra.c
@@ -771,12 +771,13 @@ create_access (tree expr, gimple stmt, bool write)
 	  disqualify_candidate (base, "Encountered a variable sized access.");
 	  return NULL;
 	}
-      if ((offset % BITS_PER_UNIT) != 0 || (size % BITS_PER_UNIT) != 0)
+      if (TREE_CODE (expr) == COMPONENT_REF
+	  && DECL_BIT_FIELD (TREE_OPERAND (expr, 1)))
 	{
-	  disqualify_candidate (base,
-				"Encountered an acces not aligned to a byte.");
+	  disqualify_candidate (base, "Encountered a bit-field access.");
 	  return NULL;
 	}
+      gcc_assert ((offset % BITS_PER_UNIT) == 0);
 
       if (ptr)
 	mark_parm_dereference (base, offset + size, stmt);
@@ -1854,13 +1855,25 @@ analyze_access_subtree (struct access *root, bool allo
       && build_ref_for_offset (NULL, TREE_TYPE (root->base), root->offset,
 			       root->type, false))
     {
+      bool new_integer_type;
+      if (TREE_CODE (root->type) == ENUMERAL_TYPE)
+	{
+	  tree rt = root->type;
+	  root->type = build_nonstandard_integer_type (TYPE_PRECISION (rt),
+						       TYPE_UNSIGNED (rt));
+	  new_integer_type = true;
+	}
+      else
+	new_integer_type = false;
+
       if (dump_file && (dump_flags & TDF_DETAILS))
 	{
 	  fprintf (dump_file, "Marking ");
 	  print_generic_expr (dump_file, root->base, 0);
-	  fprintf (dump_file, " offset: %u, size: %u: ",
+	  fprintf (dump_file, " offset: %u, size: %u ",
 		   (unsigned) root->offset, (unsigned) root->size);
-	  fprintf (dump_file, " to be replaced.\n");
+	  fprintf (dump_file, " to be replaced%s.\n",
+		   new_integer_type ? " with an integer": "");
 	}
 
       root->grp_to_be_replaced = 1;
@@ -2730,7 +2743,13 @@ sra_modify_assign (gimple *stmt, gimple_stmt_iterator 
     }
   else
     {
-      if (access_has_children_p (lacc) && access_has_children_p (racc))
+      if (access_has_children_p (lacc)
+	  && access_has_children_p (racc)
+	  /* When an access represents an unscalarizable region, it usually
+	     represents accesses with variable offset and thus must not be used
+	     to generate new memory accesses.  */
+	  && !lacc->grp_unscalarizable_region
+	  && !racc->grp_unscalarizable_region)
 	{
 	  gimple_stmt_iterator orig_gsi = *gsi;
 	  enum unscalarized_data_handling refreshed;
