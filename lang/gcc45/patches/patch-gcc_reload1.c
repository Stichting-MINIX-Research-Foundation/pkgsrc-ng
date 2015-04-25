$NetBSD$

--- gcc/reload1.c.orig	Wed Apr 20 11:05:09 2011
+++ gcc/reload1.c
@@ -4487,6 +4487,13 @@ reload_as_needed (int live_known)
 	{
 	  AND_COMPL_HARD_REG_SET (reg_reloaded_valid, call_used_reg_set);
 	  AND_COMPL_HARD_REG_SET (reg_reloaded_valid, reg_reloaded_call_part_clobbered);
+
+	  /* If this is a call to a setjmp-type function, we must not
+	     reuse any reload reg contents across the call; that will
+	     just be clobbered by other uses of the register in later
+	     code, before the longjmp.  */
+	  if (find_reg_note (insn, REG_SETJMP, NULL_RTX))
+	    CLEAR_HARD_REG_SET (reg_reloaded_valid);
 	}
     }
 
