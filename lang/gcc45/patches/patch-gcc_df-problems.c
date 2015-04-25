$NetBSD$

--- gcc/df-problems.c.orig	Tue Nov 16 22:17:17 2010
+++ gcc/df-problems.c
@@ -3748,9 +3748,22 @@ df_simulate_find_defs (rtx insn, bitmap defs)
   for (def_rec = DF_INSN_UID_DEFS (uid); *def_rec; def_rec++)
     {
       df_ref def = *def_rec;
-      /* If the def is to only part of the reg, it does
-	 not kill the other defs that reach here.  */
-      if (!(DF_REF_FLAGS (def) & (DF_REF_PARTIAL | DF_REF_CONDITIONAL)))
+      bitmap_set_bit (defs, DF_REF_REGNO (def));
+    }
+}
+
+/* Find the set of real DEFs, which are not clobbers, for INSN.  */
+
+void
+df_simulate_find_noclobber_defs (rtx insn, bitmap defs)
+{
+  df_ref *def_rec;
+  unsigned int uid = INSN_UID (insn);
+
+  for (def_rec = DF_INSN_UID_DEFS (uid); *def_rec; def_rec++)
+    {
+      df_ref def = *def_rec;
+      if (!(DF_REF_FLAGS (def) & (DF_REF_MUST_CLOBBER | DF_REF_MAY_CLOBBER)))
 	bitmap_set_bit (defs, DF_REF_REGNO (def));
     }
 }
@@ -3903,13 +3916,9 @@ df_simulate_finalize_backwards (basic_block bb, bitmap
    the block, starting with the first one.
    ----------------------------------------------------------------------------*/
 
-/* Apply the artificial uses and defs at the top of BB in a forwards
-   direction.  ??? This is wrong; defs mark the point where a pseudo
-   becomes live when scanning forwards (unless a def is unused).  Since
-   there are no REG_UNUSED notes for artificial defs, passes that
-   require artificial defs probably should not call this function
-   unless (as is the case for fwprop) they are correct when liveness
-   bitmaps are *under*estimated.  */
+/* Initialize the LIVE bitmap, which should be copied from DF_LIVE_IN or
+   DF_LR_IN for basic block BB, for forward scanning by marking artificial
+   defs live.  */
 
 void
 df_simulate_initialize_forwards (basic_block bb, bitmap live)
@@ -3921,7 +3930,7 @@ df_simulate_initialize_forwards (basic_block bb, bitma
     {
       df_ref def = *def_rec;
       if (DF_REF_FLAGS (def) & DF_REF_AT_TOP)
-	bitmap_clear_bit (live, DF_REF_REGNO (def));
+	bitmap_set_bit (live, DF_REF_REGNO (def));
     }
 }
 
@@ -3942,7 +3951,7 @@ df_simulate_one_insn_forwards (basic_block bb, rtx ins
      while here the scan is performed forwards!  So, first assume that the
      def is live, and if this is not true REG_UNUSED notes will rectify the
      situation.  */
-  df_simulate_find_defs (insn, live);
+  df_simulate_find_noclobber_defs (insn, live);
 
   /* Clear all of the registers that go dead.  */
   for (link = REG_NOTES (insn); link; link = XEXP (link, 1))
