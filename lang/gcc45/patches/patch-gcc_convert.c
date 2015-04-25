$NetBSD$

--- gcc/convert.c.orig	Sun Aug  8 15:50:17 2010
+++ gcc/convert.c
@@ -728,6 +728,15 @@ convert_to_integer (tree type, tree expr)
 	    tree arg0 = get_unwidened (TREE_OPERAND (expr, 0), type);
 	    tree arg1 = get_unwidened (TREE_OPERAND (expr, 1), type);
 
+	    /* Do not try to narrow operands of pointer subtraction;
+	       that will interfere with other folding.  */
+	    if (ex_form == MINUS_EXPR
+		&& CONVERT_EXPR_P (arg0)
+		&& CONVERT_EXPR_P (arg1)
+		&& POINTER_TYPE_P (TREE_TYPE (TREE_OPERAND (arg0, 0)))
+		&& POINTER_TYPE_P (TREE_TYPE (TREE_OPERAND (arg1, 0))))
+	      break;
+
 	    if (outprec >= BITS_PER_WORD
 		|| TRULY_NOOP_TRUNCATION (outprec, inprec)
 		|| inprec > TYPE_PRECISION (TREE_TYPE (arg0))
