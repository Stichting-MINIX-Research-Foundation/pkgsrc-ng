$NetBSD$

--- gcc/profile.c.orig	Wed Dec 30 10:53:31 2009
+++ gcc/profile.c
@@ -989,6 +989,45 @@ branch_prob (void)
 	    fprintf (dump_file, "Adding fake entry edge to bb %i\n",
 		     bb->index);
 	  make_edge (ENTRY_BLOCK_PTR, bb, EDGE_FAKE);
+	  /* Avoid bbs that have both fake entry edge and also some
+	     exit edge.  One of those edges wouldn't be added to the
+	     spanning tree, but we can't instrument any of them.  */
+	  if (have_exit_edge || need_exit_edge)
+	    {
+	      gimple_stmt_iterator gsi;
+	      gimple first;
+	      tree fndecl;
+
+	      gsi = gsi_after_labels (bb);
+#ifdef ENABLE_CHECKING
+	      gcc_assert (!gsi_end_p (gsi));
+#endif
+	      first = gsi_stmt (gsi);
+	      if (is_gimple_debug (first))
+		{
+		  gsi_next_nondebug (&gsi);
+#ifdef ENABLE_CHECKING
+		  gcc_assert (!gsi_end_p (gsi));
+#endif
+		  first = gsi_stmt (gsi);
+		}
+	      /* Don't split the bbs containing __builtin_setjmp_receiver
+		 or __builtin_setjmp_dispatcher calls.  These are very
+		 special and don't expect anything to be inserted before
+		 them.  */
+	      if (!is_gimple_call (first)
+		  || (fndecl = gimple_call_fndecl (first)) == NULL
+		  || DECL_BUILT_IN_CLASS (fndecl) != BUILT_IN_NORMAL
+		  || (DECL_FUNCTION_CODE (fndecl) != BUILT_IN_SETJMP_RECEIVER
+		      && (DECL_FUNCTION_CODE (fndecl)
+			  != BUILT_IN_SETJMP_DISPATCHER)))
+		{
+		  if (dump_file)
+		    fprintf (dump_file, "Splitting bb %i after labels\n",
+			     bb->index);
+		  split_block_after_labels (bb);
+		}
+	    }
 	}
     }
 
