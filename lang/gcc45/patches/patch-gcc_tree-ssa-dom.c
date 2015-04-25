$NetBSD$

--- gcc/tree-ssa-dom.c.orig	Tue Jul 20 12:44:16 2010
+++ gcc/tree-ssa-dom.c
@@ -209,12 +209,11 @@ initialize_hash_element (gimple stmt, tree lhs,
     {
       enum tree_code subcode = gimple_assign_rhs_code (stmt);
 
-      expr->type = NULL_TREE;
-
       switch (get_gimple_rhs_class (subcode))
         {
         case GIMPLE_SINGLE_RHS:
           expr->kind = EXPR_SINGLE;
+	  expr->type = TREE_TYPE (gimple_assign_rhs1 (stmt));
           expr->ops.single.rhs = gimple_assign_rhs1 (stmt);
           break;
         case GIMPLE_UNARY_RHS:
