$NetBSD$

--- gcc/cp/init.c.orig	Mon Apr 18 14:02:22 2011
+++ gcc/cp/init.c
@@ -1460,7 +1460,12 @@ expand_aggr_init_1 (tree binfo, tree true_exp, tree ex
 	 zero out the object first.  */
       else if (TYPE_NEEDS_CONSTRUCTING (type))
 	{
-	  init = build_zero_init (type, NULL_TREE, /*static_storage_p=*/false);
+	  tree field_size = NULL_TREE;
+	  if (exp != true_exp && CLASSTYPE_AS_BASE (type) != type)
+	    /* Don't clobber already initialized virtual bases.  */
+	    field_size = TYPE_SIZE (CLASSTYPE_AS_BASE (type));
+	  init = build_zero_init_1 (type, NULL_TREE, /*static_storage_p=*/false,
+				    field_size);
 	  init = build2 (INIT_EXPR, type, exp, init);
 	  finish_expr_stmt (init);
 	  /* And then call the constructor.  */
