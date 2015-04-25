$NetBSD$

--- gcc/tree-inline.c.orig	Tue Mar  8 13:03:34 2011
+++ gcc/tree-inline.c
@@ -4179,14 +4179,16 @@ copy_tree_r (tree *tp, int *walk_subtrees, void *data 
 					 CONSTRUCTOR_ELTS (*tp));
       *tp = new_tree;
     }
+  else if (code == STATEMENT_LIST)
+    /* We used to just abort on STATEMENT_LIST, but we can run into them
+       with statement-expressions (c++/40975).  */
+    copy_statement_list (tp);
   else if (TREE_CODE_CLASS (code) == tcc_type)
     *walk_subtrees = 0;
   else if (TREE_CODE_CLASS (code) == tcc_declaration)
     *walk_subtrees = 0;
   else if (TREE_CODE_CLASS (code) == tcc_constant)
     *walk_subtrees = 0;
-  else
-    gcc_assert (code != STATEMENT_LIST);
   return NULL_TREE;
 }
 
