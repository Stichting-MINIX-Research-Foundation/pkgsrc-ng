$NetBSD$

--- gcc/c-typeck.c.orig	Sun Jan 16 20:26:27 2011
+++ gcc/c-typeck.c
@@ -4219,6 +4219,11 @@ build_conditional_expr (location_t colon_loc, tree ife
     ret = fold_build3_loc (colon_loc, COND_EXPR, result_type, ifexp, op1, op2);
   else
     {
+      if (int_operands)
+	{
+	  op1 = remove_c_maybe_const_expr (op1);
+	  op2 = remove_c_maybe_const_expr (op2);
+	}
       ret = build3 (COND_EXPR, result_type, ifexp, op1, op2);
       if (int_operands)
 	ret = note_integer_operands (ret);
@@ -9655,6 +9660,7 @@ build_binary_op (location_t location, enum tree_code c
 		{
 		case MULT_EXPR:
 		case TRUNC_DIV_EXPR:
+		  op1 = c_save_expr (op1);
 		  imag = build2 (resultcode, real_type, imag, op1);
 		  /* Fall through.  */
 		case PLUS_EXPR:
@@ -9675,6 +9681,7 @@ build_binary_op (location_t location, enum tree_code c
 	      switch (code)
 		{
 		case MULT_EXPR:
+		  op0 = c_save_expr (op0);
 		  imag = build2 (resultcode, real_type, op0, imag);
 		  /* Fall through.  */
 		case PLUS_EXPR:
@@ -9800,7 +9807,7 @@ build_binary_op (location_t location, enum tree_code c
 		warn_for_sign_compare (location, orig_op0_folded,
 				       orig_op1_folded, op0, op1,
 				       result_type, resultcode);
-	      if (!in_late_binary_op)
+	      if (!in_late_binary_op && !int_operands)
 		{
 		  if (!op0_maybe_const || TREE_CODE (op0) != INTEGER_CST)
 		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
