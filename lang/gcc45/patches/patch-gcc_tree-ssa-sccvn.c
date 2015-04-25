$NetBSD$

--- gcc/tree-ssa-sccvn.c.orig	Wed Mar  2 13:56:41 2011
+++ gcc/tree-ssa-sccvn.c
@@ -1805,12 +1805,26 @@ print_scc (FILE *out, VEC (tree, heap) *scc)
 static inline bool
 set_ssa_val_to (tree from, tree to)
 {
-  tree currval;
+  tree currval = SSA_VAL (from);
 
-  if (from != to
-      && TREE_CODE (to) == SSA_NAME
-      && SSA_NAME_OCCURS_IN_ABNORMAL_PHI (to))
-    to = from;
+  if (from != to)
+    {
+      if (currval == from)
+	{
+	  if (dump_file && (dump_flags & TDF_DETAILS))
+	    {
+	      fprintf (dump_file, "Not changing value number of ");
+	      print_generic_expr (dump_file, from, 0);
+	      fprintf (dump_file, " from VARYING to ");
+	      print_generic_expr (dump_file, to, 0);
+	      fprintf (dump_file, "\n");
+	    }
+	  return false;
+	}
+      else if (TREE_CODE (to) == SSA_NAME
+	       && SSA_NAME_OCCURS_IN_ABNORMAL_PHI (to))
+	to = from;
+    }
 
   /* The only thing we allow as value numbers are VN_TOP, ssa_names
      and invariants.  So assert that here.  */
@@ -1826,8 +1840,6 @@ set_ssa_val_to (tree from, tree to)
       fprintf (dump_file, " to ");
       print_generic_expr (dump_file, to, 0);
     }
-
-  currval = SSA_VAL (from);
 
   if (currval != to  && !operand_equal_p (currval, to, OEP_PURE_SAME))
     {
