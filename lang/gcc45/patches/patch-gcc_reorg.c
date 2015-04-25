$NetBSD$

--- gcc/reorg.c.orig	Wed Sep 15 22:51:44 2010
+++ gcc/reorg.c
@@ -3557,9 +3557,11 @@ relax_delay_slots (rtx first)
 	    }
 	}
 
+      /* See if we have a simple (conditional) jump that is useless.  */
       if (! INSN_ANNULLED_BRANCH_P (delay_insn)
-	  && prev_active_insn (target_label) == insn
 	  && ! condjump_in_parallel_p (delay_insn)
+	  && prev_active_insn (target_label) == insn
+	  && ! BARRIER_P (prev_nonnote_insn (target_label))
 #ifdef HAVE_cc0
 	  /* If the last insn in the delay slot sets CC0 for some insn,
 	     various code assumes that it is in a delay slot.  We could
