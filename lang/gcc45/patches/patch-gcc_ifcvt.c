$NetBSD$

--- gcc/ifcvt.c.orig	Tue Nov 16 22:17:17 2010
+++ gcc/ifcvt.c
@@ -3818,7 +3818,7 @@ dead_or_predicable (basic_block test_bb, basic_block m
 		    basic_block other_bb, basic_block new_dest, int reversep)
 {
   rtx head, end, jump, earliest = NULL_RTX, old_dest, new_label = NULL_RTX;
-  bitmap merge_set = NULL;
+  bitmap merge_set = NULL, merge_set_noclobber = NULL;
   /* Number of pending changes.  */
   int n_validated_changes = 0;
 
@@ -3951,11 +3951,14 @@ dead_or_predicable (basic_block test_bb, basic_block m
 
       /* Collect:
 	   MERGE_SET = set of registers set in MERGE_BB
+	   MERGE_SET_NOCLOBBER = like MERGE_SET, but only includes registers
+	     that are really set, not just clobbered.
 	   TEST_LIVE = set of registers live at EARLIEST
-	   TEST_SET  = set of registers set between EARLIEST and the
-		       end of the block.  */
+	   TEST_SET = set of registers set between EARLIEST and the
+	     end of the block.  */
 
       merge_set = BITMAP_ALLOC (&reg_obstack);
+      merge_set_noclobber = BITMAP_ALLOC (&reg_obstack);
 
       /* If we allocated new pseudos (e.g. in the conditional move
 	 expander called from noce_emit_cmove), we must resize the
@@ -3967,13 +3970,8 @@ dead_or_predicable (basic_block test_bb, basic_block m
 	{
 	  if (NONDEBUG_INSN_P (insn))
 	    {
-	      unsigned int uid = INSN_UID (insn);
-	      df_ref *def_rec;
-	      for (def_rec = DF_INSN_UID_DEFS (uid); *def_rec; def_rec++)
-		{
-		  df_ref def = *def_rec;
-		  bitmap_set_bit (merge_set, DF_REF_REGNO (def));
-		}
+	      df_simulate_find_defs (insn, merge_set);
+	      df_simulate_find_noclobber_defs (insn, merge_set_noclobber);
 	    }
 	}
 
@@ -3984,7 +3982,7 @@ dead_or_predicable (basic_block test_bb, basic_block m
 	  unsigned i;
 	  bitmap_iterator bi;
 
-          EXECUTE_IF_SET_IN_BITMAP (merge_set, 0, i, bi)
+          EXECUTE_IF_SET_IN_BITMAP (merge_set_noclobber, 0, i, bi)
 	    {
 	      if (i < FIRST_PSEUDO_REGISTER
 		  && ! fixed_regs[i]
@@ -4015,12 +4013,14 @@ dead_or_predicable (basic_block test_bb, basic_block m
 	}
 
       /* We can perform the transformation if
-	   MERGE_SET & (TEST_SET | TEST_LIVE)
+	   MERGE_SET_NOCLOBBER & TEST_SET
 	 and
+	   MERGE_SET & TEST_LIVE
+	 and
 	   TEST_SET & DF_LIVE_IN (merge_bb)
 	 are empty.  */
 
-      if (bitmap_intersect_p (merge_set, test_set)
+      if (bitmap_intersect_p (merge_set_noclobber, test_set)
 	  || bitmap_intersect_p (merge_set, test_live)
 	  || bitmap_intersect_p (test_set, df_get_live_in (merge_bb)))
 	intersect = true;
@@ -4104,10 +4104,11 @@ dead_or_predicable (basic_block test_bb, basic_block m
 	  unsigned i;
 	  bitmap_iterator bi;
 
-	  EXECUTE_IF_SET_IN_BITMAP (merge_set, 0, i, bi)
+	  EXECUTE_IF_SET_IN_BITMAP (merge_set_noclobber, 0, i, bi)
 	    remove_reg_equal_equiv_notes_for_regno (i);
 
 	  BITMAP_FREE (merge_set);
+	  BITMAP_FREE (merge_set_noclobber);
 	}
 
       reorder_insns (head, end, PREV_INSN (earliest));
@@ -4128,7 +4129,10 @@ dead_or_predicable (basic_block test_bb, basic_block m
   cancel_changes (0);
  fail:
   if (merge_set)
-    BITMAP_FREE (merge_set);
+    {
+      BITMAP_FREE (merge_set);
+      BITMAP_FREE (merge_set_noclobber);
+    }
   return FALSE;
 }
 
