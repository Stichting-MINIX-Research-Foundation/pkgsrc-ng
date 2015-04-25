$NetBSD$

--- gcc/c-decl.c.orig	Thu Nov 11 20:40:32 2010
+++ gcc/c-decl.c
@@ -3909,7 +3909,7 @@ start_decl (struct c_declarator *declarator, struct c_
     return 0;
 
   if (expr)
-    add_stmt (expr);
+    add_stmt (fold_convert (void_type_node, expr));
 
   if (TREE_CODE (decl) != FUNCTION_DECL && MAIN_NAME_P (DECL_NAME (decl)))
     warning (OPT_Wmain, "%q+D is usually a function", decl);
@@ -7385,7 +7385,8 @@ start_function (struct c_declspecs *declspecs, struct 
 
   /* If the declarator is not suitable for a function definition,
      cause a syntax error.  */
-  if (decl1 == 0)
+  if (decl1 == 0
+      || TREE_CODE (decl1) != FUNCTION_DECL)
     return 0;
 
   loc = DECL_SOURCE_LOCATION (decl1);
