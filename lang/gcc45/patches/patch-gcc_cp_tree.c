$NetBSD$

--- gcc/cp/tree.c.orig	Sun Feb 27 17:11:19 2011
+++ gcc/cp/tree.c
@@ -1732,7 +1732,11 @@ bot_manip (tree* tp, int* walk_subtrees, void* data)
       tree u;
 
       if (TREE_CODE (TREE_OPERAND (t, 1)) == AGGR_INIT_EXPR)
-	u = build_cplus_new (TREE_TYPE (t), TREE_OPERAND (t, 1));
+	{
+	  u = build_cplus_new (TREE_TYPE (t), TREE_OPERAND (t, 1));
+	  if (AGGR_INIT_ZERO_FIRST (TREE_OPERAND (t, 1)))
+	    AGGR_INIT_ZERO_FIRST (TREE_OPERAND (u, 1)) = true;
+	}
       else
 	u = build_target_expr_with_type (TREE_OPERAND (t, 1), TREE_TYPE (t));
 
@@ -2954,7 +2958,8 @@ stabilize_expr (tree exp, tree* initp)
   if (!TREE_SIDE_EFFECTS (exp))
     init_expr = NULL_TREE;
   else if (!real_lvalue_p (exp)
-	   || !TYPE_NEEDS_CONSTRUCTING (TREE_TYPE (exp)))
+	   || (!TYPE_NEEDS_CONSTRUCTING (TREE_TYPE (exp))
+	       && !TYPE_HAS_NONTRIVIAL_DESTRUCTOR (TREE_TYPE (exp))))
     {
       init_expr = get_target_expr (exp);
       exp = TARGET_EXPR_SLOT (init_expr);
