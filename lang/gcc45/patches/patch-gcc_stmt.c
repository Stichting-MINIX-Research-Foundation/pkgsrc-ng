$NetBSD$

--- gcc/stmt.c.orig	Fri Oct 29 16:58:36 2010
+++ gcc/stmt.c
@@ -1232,11 +1232,11 @@ check_operand_nalternatives (tree outputs, tree inputs
 static bool
 check_unique_operand_names (tree outputs, tree inputs, tree labels)
 {
-  tree i, j;
+  tree i, j, i_name = NULL_TREE;
 
   for (i = outputs; i ; i = TREE_CHAIN (i))
     {
-      tree i_name = TREE_PURPOSE (TREE_PURPOSE (i));
+      i_name = TREE_PURPOSE (TREE_PURPOSE (i));
       if (! i_name)
 	continue;
 
@@ -1247,7 +1247,7 @@ check_unique_operand_names (tree outputs, tree inputs,
 
   for (i = inputs; i ; i = TREE_CHAIN (i))
     {
-      tree i_name = TREE_PURPOSE (TREE_PURPOSE (i));
+      i_name = TREE_PURPOSE (TREE_PURPOSE (i));
       if (! i_name)
 	continue;
 
@@ -1261,7 +1261,7 @@ check_unique_operand_names (tree outputs, tree inputs,
 
   for (i = labels; i ; i = TREE_CHAIN (i))
     {
-      tree i_name = TREE_PURPOSE (i);
+      i_name = TREE_PURPOSE (i);
       if (! i_name)
 	continue;
 
@@ -1276,8 +1276,7 @@ check_unique_operand_names (tree outputs, tree inputs,
   return true;
 
  failure:
-  error ("duplicate asm operand name %qs",
-	 TREE_STRING_POINTER (TREE_PURPOSE (TREE_PURPOSE (i))));
+  error ("duplicate asm operand name %qs", TREE_STRING_POINTER (i_name));
   return false;
 }
 
