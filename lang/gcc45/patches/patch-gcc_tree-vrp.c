$NetBSD$

--- gcc/tree-vrp.c.orig	Tue Jan 25 09:48:07 2011
+++ gcc/tree-vrp.c
@@ -1,5 +1,5 @@
 /* Support routines for Value Range Propagation (VRP).
-   Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010
+   Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011
    Free Software Foundation, Inc.
    Contributed by Diego Novillo <dnovillo@redhat.com>.
 
@@ -1445,7 +1445,7 @@ extract_range_from_assert (value_range_t *vr_p, tree e
 
   limit = avoid_overflow_infinity (limit);
 
-  type = TREE_TYPE (limit);
+  type = TREE_TYPE (var);
   gcc_assert (limit != var);
 
   /* For pointer arithmetic, we only keep track of pointer equality
@@ -1619,8 +1619,8 @@ extract_range_from_assert (value_range_t *vr_p, tree e
 	  /* For LT_EXPR, we create the range [MIN, MAX - 1].  */
 	  if (cond_code == LT_EXPR)
 	    {
-	      tree one = build_int_cst (type, 1);
-	      max = fold_build2 (MINUS_EXPR, type, max, one);
+	      tree one = build_int_cst (TREE_TYPE (max), 1);
+	      max = fold_build2 (MINUS_EXPR, TREE_TYPE (max), max, one);
 	      if (EXPR_P (max))
 		TREE_NO_WARNING (max) = 1;
 	    }
@@ -1654,8 +1654,8 @@ extract_range_from_assert (value_range_t *vr_p, tree e
 	  /* For GT_EXPR, we create the range [MIN + 1, MAX].  */
 	  if (cond_code == GT_EXPR)
 	    {
-	      tree one = build_int_cst (type, 1);
-	      min = fold_build2 (PLUS_EXPR, type, min, one);
+	      tree one = build_int_cst (TREE_TYPE (min), 1);
+	      min = fold_build2 (PLUS_EXPR, TREE_TYPE (min), min, one);
 	      if (EXPR_P (min))
 		TREE_NO_WARNING (min) = 1;
 	    }
@@ -2257,18 +2257,28 @@ extract_range_from_binary_expr (value_range_t *vr,
 	 op0 + op1 == 0, so we cannot claim that the sum is in ~[0,0].
 	 Note that we are guaranteed to have vr0.type == vr1.type at
 	 this point.  */
-      if (code == PLUS_EXPR && vr0.type == VR_ANTI_RANGE)
+      if (vr0.type == VR_ANTI_RANGE)
 	{
-	  set_value_range_to_varying (vr);
-	  return;
+	  if (code == PLUS_EXPR)
+	    {
+	      set_value_range_to_varying (vr);
+	      return;
+	    }
+	  /* For MIN_EXPR and MAX_EXPR with two VR_ANTI_RANGEs,
+	     the resulting VR_ANTI_RANGE is the same - intersection
+	     of the two ranges.  */
+	  min = vrp_int_const_binop (MAX_EXPR, vr0.min, vr1.min);
+	  max = vrp_int_const_binop (MIN_EXPR, vr0.max, vr1.max);
 	}
+      else
+	{
+	  /* For operations that make the resulting range directly
+	     proportional to the original ranges, apply the operation to
+	     the same end of each range.  */
+	  min = vrp_int_const_binop (code, vr0.min, vr1.min);
+	  max = vrp_int_const_binop (code, vr0.max, vr1.max);
+	}
 
-      /* For operations that make the resulting range directly
-	 proportional to the original ranges, apply the operation to
-	 the same end of each range.  */
-      min = vrp_int_const_binop (code, vr0.min, vr1.min);
-      max = vrp_int_const_binop (code, vr0.max, vr1.max);
-
       /* If both additions overflowed the range kind is still correct.
 	 This happens regularly with subtracting something in unsigned
 	 arithmetic.
@@ -4505,28 +4515,35 @@ find_conditional_asserts (basic_block bb, gimple last)
   return need_assert;
 }
 
-/* Compare two case labels sorting first by the destination label uid
+struct case_info
+{
+  tree expr;
+  basic_block bb;
+};
+
+/* Compare two case labels sorting first by the destination bb index
    and then by the case value.  */
 
 static int
 compare_case_labels (const void *p1, const void *p2)
 {
-  const_tree const case1 = *(const_tree const*)p1;
-  const_tree const case2 = *(const_tree const*)p2;
-  unsigned int uid1 = DECL_UID (CASE_LABEL (case1));
-  unsigned int uid2 = DECL_UID (CASE_LABEL (case2));
+  const struct case_info *ci1 = (const struct case_info *) p1;
+  const struct case_info *ci2 = (const struct case_info *) p2;
+  int idx1 = ci1->bb->index;
+  int idx2 = ci2->bb->index;
 
-  if (uid1 < uid2)
+  if (idx1 < idx2)
     return -1;
-  else if (uid1 == uid2)
+  else if (idx1 == idx2)
     {
       /* Make sure the default label is first in a group.  */
-      if (!CASE_LOW (case1))
+      if (!CASE_LOW (ci1->expr))
 	return -1;
-      else if (!CASE_LOW (case2))
+      else if (!CASE_LOW (ci2->expr))
 	return 1;
       else
-        return tree_int_cst_compare (CASE_LOW (case1), CASE_LOW (case2));
+	return tree_int_cst_compare (CASE_LOW (ci1->expr),
+				     CASE_LOW (ci2->expr));
     }
   else
     return 1;
@@ -4547,8 +4564,8 @@ find_switch_asserts (basic_block bb, gimple last)
   gimple_stmt_iterator bsi;
   tree op;
   edge e;
-  tree vec2;
-  size_t n = gimple_switch_num_labels(last);
+  struct case_info *ci;
+  size_t n = gimple_switch_num_labels (last);
 #if GCC_VERSION >= 4000
   unsigned int idx;
 #else
@@ -4563,36 +4580,38 @@ find_switch_asserts (basic_block bb, gimple last)
     return false;
 
   /* Build a vector of case labels sorted by destination label.  */
-  vec2 = make_tree_vec (n);
+  ci = XNEWVEC (struct case_info, n);
   for (idx = 0; idx < n; ++idx)
-    TREE_VEC_ELT (vec2, idx) = gimple_switch_label (last, idx);
-  qsort (&TREE_VEC_ELT (vec2, 0), n, sizeof (tree), compare_case_labels);
+    {
+      ci[idx].expr = gimple_switch_label (last, idx);
+      ci[idx].bb = label_to_block (CASE_LABEL (ci[idx].expr));
+    }
+  qsort (ci, n, sizeof (struct case_info), compare_case_labels);
 
   for (idx = 0; idx < n; ++idx)
     {
       tree min, max;
-      tree cl = TREE_VEC_ELT (vec2, idx);
+      tree cl = ci[idx].expr;
+      basic_block cbb = ci[idx].bb;
 
       min = CASE_LOW (cl);
       max = CASE_HIGH (cl);
 
       /* If there are multiple case labels with the same destination
 	 we need to combine them to a single value range for the edge.  */
-      if (idx + 1 < n
-	  && CASE_LABEL (cl) == CASE_LABEL (TREE_VEC_ELT (vec2, idx + 1)))
+      if (idx + 1 < n && cbb == ci[idx + 1].bb)
 	{
 	  /* Skip labels until the last of the group.  */
 	  do {
 	    ++idx;
-	  } while (idx < n
-		   && CASE_LABEL (cl) == CASE_LABEL (TREE_VEC_ELT (vec2, idx)));
+	  } while (idx < n && cbb == ci[idx].bb);
 	  --idx;
 
 	  /* Pick up the maximum of the case label range.  */
-	  if (CASE_HIGH (TREE_VEC_ELT (vec2, idx)))
-	    max = CASE_HIGH (TREE_VEC_ELT (vec2, idx));
+	  if (CASE_HIGH (ci[idx].expr))
+	    max = CASE_HIGH (ci[idx].expr);
 	  else
-	    max = CASE_LOW (TREE_VEC_ELT (vec2, idx));
+	    max = CASE_LOW (ci[idx].expr);
 	}
 
       /* Nothing to do if the range includes the default label until we
@@ -4601,7 +4620,7 @@ find_switch_asserts (basic_block bb, gimple last)
 	continue;
 
       /* Find the edge to register the assert expr on.  */
-      e = find_edge (bb, label_to_block (CASE_LABEL (cl)));
+      e = find_edge (bb, cbb);
 
       /* Register the necessary assertions for the operand in the
 	 SWITCH_EXPR.  */
@@ -4619,6 +4638,7 @@ find_switch_asserts (basic_block bb, gimple last)
 	}
     }
 
+  XDELETEVEC (ci);
   return need_assert;
 }
 
