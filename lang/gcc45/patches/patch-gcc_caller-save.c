$NetBSD$

--- gcc/caller-save.c.orig	Wed Mar 16 20:19:14 2011
+++ gcc/caller-save.c
@@ -439,101 +439,93 @@ saved_hard_reg_compare_func (const void *v1p, const vo
 void
 setup_save_areas (void)
 {
-  int i, j, k;
-  unsigned int r;
+  int i, j, k, freq;
   HARD_REG_SET hard_regs_used;
+  struct saved_hard_reg *saved_reg;
+  rtx insn;
+  struct insn_chain *chain, *next;
+  unsigned int regno;
+  HARD_REG_SET hard_regs_to_save, used_regs, this_insn_sets;
+  reg_set_iterator rsi;
 
-  /* Allocate space in the save area for the largest multi-register
-     pseudos first, then work backwards to single register
-     pseudos.  */
-
-  /* Find and record all call-used hard-registers in this function.  */
   CLEAR_HARD_REG_SET (hard_regs_used);
-  for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)
-    if (reg_renumber[i] >= 0 && REG_N_CALLS_CROSSED (i) > 0)
-      {
-	unsigned int regno = reg_renumber[i];
-	unsigned int endregno
-	  = end_hard_regno (GET_MODE (regno_reg_rtx[i]), regno);
-	for (r = regno; r < endregno; r++)
-	  if (call_used_regs[r])
-	    SET_HARD_REG_BIT (hard_regs_used, r);
-      }
 
-  if (optimize && flag_ira_share_save_slots)
+  /* Find every CALL_INSN and record which hard regs are live across the
+     call into HARD_REG_MAP and HARD_REGS_USED.  */
+  initiate_saved_hard_regs ();
+  /* Create hard reg saved regs.  */
+  for (chain = reload_insn_chain; chain != 0; chain = next)
     {
-      rtx insn, slot;
-      struct insn_chain *chain, *next;
-      char *saved_reg_conflicts;
-      unsigned int regno;
-      int next_k, freq;
-      struct saved_hard_reg *saved_reg, *saved_reg2, *saved_reg3;
-      int call_saved_regs_num;
-      struct saved_hard_reg *call_saved_regs[FIRST_PSEUDO_REGISTER];
-      HARD_REG_SET hard_regs_to_save, used_regs, this_insn_sets;
-      reg_set_iterator rsi;
-      int best_slot_num;
-      int prev_save_slots_num;
-      rtx prev_save_slots[FIRST_PSEUDO_REGISTER];
+      insn = chain->insn;
+      next = chain->next;
+      if (!CALL_P (insn)
+	  || find_reg_note (insn, REG_NORETURN, NULL))
+	continue;
+      freq = REG_FREQ_FROM_BB (BLOCK_FOR_INSN (insn));
+      REG_SET_TO_HARD_REG_SET (hard_regs_to_save,
+			       &chain->live_throughout);
+      COPY_HARD_REG_SET (used_regs, call_used_reg_set);
 
-      initiate_saved_hard_regs ();
-      /* Create hard reg saved regs.  */
-      for (chain = reload_insn_chain; chain != 0; chain = next)
+      /* Record all registers set in this call insn.  These don't
+	 need to be saved.  N.B. the call insn might set a subreg
+	 of a multi-hard-reg pseudo; then the pseudo is considered
+	 live during the call, but the subreg that is set
+	 isn't.  */
+      CLEAR_HARD_REG_SET (this_insn_sets);
+      note_stores (PATTERN (insn), mark_set_regs, &this_insn_sets);
+      /* Sibcalls are considered to set the return value.  */
+      if (SIBLING_CALL_P (insn) && crtl->return_rtx)
+	mark_set_regs (crtl->return_rtx, NULL_RTX, &this_insn_sets);
+
+      AND_COMPL_HARD_REG_SET (used_regs, call_fixed_reg_set);
+      AND_COMPL_HARD_REG_SET (used_regs, this_insn_sets);
+      AND_HARD_REG_SET (hard_regs_to_save, used_regs);
+      for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
+	if (TEST_HARD_REG_BIT (hard_regs_to_save, regno))
+	  {
+	    if (hard_reg_map[regno] != NULL)
+	      hard_reg_map[regno]->call_freq += freq;
+	    else
+	      saved_reg = new_saved_hard_reg (regno, freq);
+	    SET_HARD_REG_BIT (hard_regs_used, regno);
+	  }
+      /* Look through all live pseudos, mark their hard registers.  */
+      EXECUTE_IF_SET_IN_REG_SET
+	(&chain->live_throughout, FIRST_PSEUDO_REGISTER, regno, rsi)
 	{
-	  insn = chain->insn;
-	  next = chain->next;
-	  if (!CALL_P (insn)
-	      || find_reg_note (insn, REG_NORETURN, NULL))
+	  int r = reg_renumber[regno];
+	  int bound;
+
+	  if (r < 0)
 	    continue;
-	  freq = REG_FREQ_FROM_BB (BLOCK_FOR_INSN (insn));
-	  REG_SET_TO_HARD_REG_SET (hard_regs_to_save,
-				   &chain->live_throughout);
-	  COPY_HARD_REG_SET (used_regs, call_used_reg_set);
 
-	  /* Record all registers set in this call insn.  These don't
-	     need to be saved.  N.B. the call insn might set a subreg
-	     of a multi-hard-reg pseudo; then the pseudo is considered
-	     live during the call, but the subreg that is set
-	     isn't.  */
-	  CLEAR_HARD_REG_SET (this_insn_sets);
-	  note_stores (PATTERN (insn), mark_set_regs, &this_insn_sets);
-	  /* Sibcalls are considered to set the return value.  */
-	  if (SIBLING_CALL_P (insn) && crtl->return_rtx)
-	    mark_set_regs (crtl->return_rtx, NULL_RTX, &this_insn_sets);
-
-	  AND_COMPL_HARD_REG_SET (used_regs, call_fixed_reg_set);
-	  AND_COMPL_HARD_REG_SET (used_regs, this_insn_sets);
-	  AND_HARD_REG_SET (hard_regs_to_save, used_regs);
-	  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
-	    if (TEST_HARD_REG_BIT (hard_regs_to_save, regno))
+	  bound = r + hard_regno_nregs[r][PSEUDO_REGNO_MODE (regno)];
+	  for (; r < bound; r++)
+	    if (TEST_HARD_REG_BIT (used_regs, r))
 	      {
-		if (hard_reg_map[regno] != NULL)
-		  hard_reg_map[regno]->call_freq += freq;
+		if (hard_reg_map[r] != NULL)
+		  hard_reg_map[r]->call_freq += freq;
 		else
-		  saved_reg = new_saved_hard_reg (regno, freq);
+		  saved_reg = new_saved_hard_reg (r, freq);
+		 SET_HARD_REG_BIT (hard_regs_to_save, r);
+		 SET_HARD_REG_BIT (hard_regs_used, r);
 	      }
-	  /* Look through all live pseudos, mark their hard registers.  */
-	  EXECUTE_IF_SET_IN_REG_SET
-	    (&chain->live_throughout, FIRST_PSEUDO_REGISTER, regno, rsi)
-	    {
-	      int r = reg_renumber[regno];
-	      int bound;
+	}
+    }
 
-	      if (r < 0)
-		continue;
+  /* If requested, figure out which hard regs can share save slots.  */
+  if (optimize && flag_ira_share_save_slots)
+    {
+      rtx slot;
+      char *saved_reg_conflicts;
+      int next_k;
+      struct saved_hard_reg *saved_reg2, *saved_reg3;
+      int call_saved_regs_num;
+      struct saved_hard_reg *call_saved_regs[FIRST_PSEUDO_REGISTER];
+      int best_slot_num;
+      int prev_save_slots_num;
+      rtx prev_save_slots[FIRST_PSEUDO_REGISTER];
 
-	      bound = r + hard_regno_nregs[r][PSEUDO_REGNO_MODE (regno)];
-	      for (; r < bound; r++)
-		if (TEST_HARD_REG_BIT (used_regs, r))
-		  {
-		    if (hard_reg_map[r] != NULL)
-		      hard_reg_map[r]->call_freq += freq;
-		    else
-		      saved_reg = new_saved_hard_reg (r, freq);
-		    SET_HARD_REG_BIT (hard_regs_to_save, r);
-		  }
-	    }
-	}
       /* Find saved hard register conflicts.  */
       saved_reg_conflicts = (char *) xmalloc (saved_regs_num * saved_regs_num);
       memset (saved_reg_conflicts, 0, saved_regs_num * saved_regs_num);
@@ -691,8 +683,10 @@ setup_save_areas (void)
     }
   else
     {
-      /* Now run through all the call-used hard-registers and allocate
-	 space for them in the caller-save area.  Try to allocate space
+      /* We are not sharing slots. 
+
+	 Run through all the call-used hard-registers and allocate
+	 space for each in the caller-save area.  Try to allocate space
 	 in a manner which allows multi-register saves/restores to be done.  */
 
       for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
