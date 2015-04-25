$NetBSD$

--- gcc/cp/typeck.c.orig	Wed Apr 20 06:31:07 2011
+++ gcc/cp/typeck.c
@@ -4297,6 +4297,7 @@ cp_build_binary_op (location_t location,
 		{
 		case MULT_EXPR:
 		case TRUNC_DIV_EXPR:
+		  op1 = save_expr (op1);
 		  imag = build2 (resultcode, real_type, imag, op1);
 		  /* Fall through.  */
 		case PLUS_EXPR:
@@ -4315,6 +4316,7 @@ cp_build_binary_op (location_t location,
 	      switch (code)
 		{
 		case MULT_EXPR:
+		  op0 = save_expr (op0);
 		  imag = build2 (resultcode, real_type, op0, imag);
 		  /* Fall through.  */
 		case PLUS_EXPR:
@@ -5672,8 +5674,18 @@ build_static_cast_1 (tree type, tree expr, bool c_cast
       && reference_related_p (TREE_TYPE (type), intype)
       && (c_cast_p || at_least_as_qualified_p (TREE_TYPE (type), intype)))
     {
-      expr = build_typed_address (expr, type);
-      return convert_from_reference (expr);
+      /* Handle the lvalue case here by casting to lvalue reference and
+	 then changing it to an rvalue reference.  Casting an xvalue to
+	 rvalue reference will be handled by the main code path.  */
+      tree lref = cp_build_reference_type (TREE_TYPE (type), false);
+      result = (perform_direct_initialization_if_possible
+		(lref, expr, c_cast_p, complain));
+      result = cp_fold_convert (type, result);
+      /* Make sure we don't fold back down to a named rvalue reference,
+	 because that would be an lvalue.  */
+      if (DECL_P (result))
+	result = build1 (NON_LVALUE_EXPR, type, result);
+      return convert_from_reference (result);
     }
 
   orig = expr;
