$NetBSD$

--- gcc/c-common.c.orig	Thu Apr  7 18:25:50 2011
+++ gcc/c-common.c
@@ -4031,14 +4031,15 @@ c_common_truthvalue_conversion (location_t location, t
       /* Distribute the conversion into the arms of a COND_EXPR.  */
       if (c_dialect_cxx ())
 	{
+	  tree op1 = TREE_OPERAND (expr, 1);
+	  tree op2 = TREE_OPERAND (expr, 2);
+	  /* In C++ one of the arms might have void type if it is throw.  */
+	  if (!VOID_TYPE_P (TREE_TYPE (op1)))
+	    op1 = c_common_truthvalue_conversion (location, op1);
+	  if (!VOID_TYPE_P (TREE_TYPE (op2)))
+	    op2 = c_common_truthvalue_conversion (location, op2);
 	  expr = fold_build3_loc (location, COND_EXPR, truthvalue_type_node,
-			      TREE_OPERAND (expr, 0),
-			      c_common_truthvalue_conversion (location,
-							      TREE_OPERAND (expr,
-									    1)),
-			      c_common_truthvalue_conversion (location,
-							      TREE_OPERAND (expr,
-									    2)));
+				  TREE_OPERAND (expr, 0), op1, op2);
 	  goto ret;
 	}
       else
