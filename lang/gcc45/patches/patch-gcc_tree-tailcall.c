$NetBSD$

--- gcc/tree-tailcall.c.orig	Fri Apr 23 15:47:44 2010
+++ gcc/tree-tailcall.c
@@ -1007,6 +1007,14 @@ tree_optimize_tail_calls_1 (bool opt_tailcalls)
 					     integer_one_node);
     }
 
+  if (a_acc || m_acc)
+    {
+      /* When the tail call elimination using accumulators is performed,
+	 statements adding the accumulated value are inserted at all exits.
+	 This turns all other tail calls to non-tail ones.  */
+      opt_tailcalls = false;
+    }
+
   for (; tailcalls; tailcalls = next)
     {
       next = tailcalls->next;
