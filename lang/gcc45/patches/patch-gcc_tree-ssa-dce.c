$NetBSD$

--- gcc/tree-ssa-dce.c.orig	Wed Nov 17 10:46:36 2010
+++ gcc/tree-ssa-dce.c
@@ -509,7 +509,14 @@ mark_aliased_reaching_defs_necessary_1 (ao_ref *ref, t
 
   /* If the stmt lhs kills ref, then we can stop walking.  */
   if (gimple_has_lhs (def_stmt)
-      && TREE_CODE (gimple_get_lhs (def_stmt)) != SSA_NAME)
+      && TREE_CODE (gimple_get_lhs (def_stmt)) != SSA_NAME
+      /* The assignment is not necessarily carried out if it can throw
+         and we can catch it in the current function where we could inspect
+	 the previous value.
+         ???  We only need to care about the RHS throwing.  For aggregate
+	 assignments or similar calls and non-call exceptions the LHS
+	 might throw as well.  */
+      && !stmt_can_throw_internal (def_stmt))
     {
       tree base, lhs = gimple_get_lhs (def_stmt);
       HOST_WIDE_INT size, offset, max_size;
