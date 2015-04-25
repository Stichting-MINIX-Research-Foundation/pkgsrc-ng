$NetBSD$

--- gcc/tree-scalar-evolution.c.orig	Fri Apr  2 19:54:46 2010
+++ gcc/tree-scalar-evolution.c
@@ -2557,7 +2557,8 @@ instantiate_scev_r (basic_block instantiate_below,
   if (size_expr++ > PARAM_VALUE (PARAM_SCEV_MAX_EXPR_SIZE))
     return chrec_dont_know;
 
-  if (automatically_generated_chrec_p (chrec)
+  if (chrec == NULL_TREE
+      || automatically_generated_chrec_p (chrec)
       || is_gimple_min_invariant (chrec))
     return chrec;
 
