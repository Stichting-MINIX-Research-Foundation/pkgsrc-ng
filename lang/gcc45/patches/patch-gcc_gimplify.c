$NetBSD$

--- gcc/gimplify.c.orig	Thu Apr  7 18:27:20 2011
+++ gcc/gimplify.c
@@ -1953,8 +1953,14 @@ gimplify_compound_lval (tree *expr_p, gimple_seq *pre_
 		  ret = MIN (ret, tret);
 		}
 	    }
+	  else
+	    {
+	      tret = gimplify_expr (&TREE_OPERAND (t, 2), pre_p, post_p,
+				    is_gimple_reg, fb_rvalue);
+	      ret = MIN (ret, tret);
+	    }
 
-	  if (!TREE_OPERAND (t, 3))
+	  if (TREE_OPERAND (t, 3) == NULL_TREE)
 	    {
 	      tree elmt_type = TREE_TYPE (TREE_TYPE (TREE_OPERAND (t, 0)));
 	      tree elmt_size = unshare_expr (array_ref_element_size (t));
@@ -1973,11 +1979,17 @@ gimplify_compound_lval (tree *expr_p, gimple_seq *pre_
 		  ret = MIN (ret, tret);
 		}
 	    }
+	  else
+	    {
+	      tret = gimplify_expr (&TREE_OPERAND (t, 3), pre_p, post_p,
+				    is_gimple_reg, fb_rvalue);
+	      ret = MIN (ret, tret);
+	    }
 	}
       else if (TREE_CODE (t) == COMPONENT_REF)
 	{
 	  /* Set the field offset into T and gimplify it.  */
-	  if (!TREE_OPERAND (t, 2))
+	  if (TREE_OPERAND (t, 2) == NULL_TREE)
 	    {
 	      tree offset = unshare_expr (component_ref_field_offset (t));
 	      tree field = TREE_OPERAND (t, 1);
@@ -1996,6 +2008,12 @@ gimplify_compound_lval (tree *expr_p, gimple_seq *pre_
 		  ret = MIN (ret, tret);
 		}
 	    }
+	  else
+	    {
+	      tret = gimplify_expr (&TREE_OPERAND (t, 2), pre_p, post_p,
+				    is_gimple_reg, fb_rvalue);
+	      ret = MIN (ret, tret);
+	    }
 	}
     }
 
@@ -2496,7 +2514,9 @@ shortcut_cond_r (tree pred, tree *true_label_p, tree *
 			   new_locus);
       append_to_statement_list (t, &expr);
     }
-  else if (TREE_CODE (pred) == COND_EXPR)
+  else if (TREE_CODE (pred) == COND_EXPR
+	   && !VOID_TYPE_P (TREE_TYPE (TREE_OPERAND (pred, 1)))
+	   && !VOID_TYPE_P (TREE_TYPE (TREE_OPERAND (pred, 2))))
     {
       location_t new_locus;
 
@@ -2504,7 +2524,10 @@ shortcut_cond_r (tree pred, tree *true_label_p, tree *
 	 if (a)
 	   if (b) goto yes; else goto no;
 	 else
-	   if (c) goto yes; else goto no;  */
+	   if (c) goto yes; else goto no;
+
+	 Don't do this if one of the arms has void type, which can happen
+	 in C++ when the arm is throw.  */
 
       /* Keep the original source location on the first 'if'.  Set the source
 	 location of the ? on the second 'if'.  */
