$NetBSD$

--- gcc/var-tracking.c.orig	Sat Nov  6 06:28:59 2010
+++ gcc/var-tracking.c
@@ -4134,8 +4134,9 @@ find_mem_expr_in_1pdv (tree expr, rtx val, htab_t vars
   VALUE_RECURSED_INTO (val) = true;
 
   for (node = var->var_part[0].loc_chain; node; node = node->next)
-    if (MEM_P (node->loc) && MEM_EXPR (node->loc) == expr
-	&& MEM_OFFSET (node->loc) == 0)
+    if (MEM_P (node->loc)
+	&& MEM_EXPR (node->loc) == expr
+	&& INT_MEM_OFFSET (node->loc) == 0)
       {
 	where = node;
 	break;
@@ -4198,11 +4199,10 @@ dataflow_set_preserve_mem_locs (void **slot, void *dat
 	{
 	  for (loc = var->var_part[0].loc_chain; loc; loc = loc->next)
 	    {
-	      /* We want to remove dying MEMs that doesn't refer to
-		 DECL.  */
+	      /* We want to remove dying MEMs that doesn't refer to DECL.  */
 	      if (GET_CODE (loc->loc) == MEM
 		  && (MEM_EXPR (loc->loc) != decl
-		      || MEM_OFFSET (loc->loc))
+		      || INT_MEM_OFFSET (loc->loc) != 0)
 		  && !mem_dies_at_call (loc->loc))
 		break;
 	      /* We want to move here MEMs that do refer to DECL.  */
@@ -4246,7 +4246,7 @@ dataflow_set_preserve_mem_locs (void **slot, void *dat
 
 	  if (GET_CODE (loc->loc) != MEM
 	      || (MEM_EXPR (loc->loc) == decl
-		  && MEM_OFFSET (loc->loc) == 0)
+		  && INT_MEM_OFFSET (loc->loc) == 0)
 	      || !mem_dies_at_call (loc->loc))
 	    {
 	      if (old_loc != loc->loc && emit_notes)
