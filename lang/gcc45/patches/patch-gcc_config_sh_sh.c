$NetBSD$

--- gcc/config/sh/sh.c.orig	Wed May  5 22:12:17 2010
+++ gcc/config/sh/sh.c
@@ -1945,7 +1945,10 @@ expand_cbranchdi4 (rtx *operands, enum rtx_code compar
 	  else if (op2h != CONST0_RTX (SImode))
 	    msw_taken = LTU;
 	  else
-	    break;
+	    {
+	      msw_skip = swap_condition (LTU);
+	      break;
+	    }
 	  msw_skip = swap_condition (msw_taken);
 	}
       break;
@@ -1998,6 +2001,13 @@ expand_cbranchdi4 (rtx *operands, enum rtx_code compar
 	{
 	  operands[1] = op1h;
 	  operands[2] = op2h;
+	  if (reload_completed
+	      && ! arith_reg_or_0_operand (op2h, SImode)
+	      && (true_regnum (op1h) || (comparison != EQ && comparison != NE)))
+	    {
+	      emit_move_insn (scratch, operands[2]);
+	      operands[2] = scratch;
+	    }
 	}
 
       operands[3] = skip_label = gen_label_rtx ();
@@ -11428,10 +11438,6 @@ sh_output_mi_thunk (FILE *file, tree thunk_fndecl ATTR
     }
 
   sh_reorg ();
-
-  if (optimize > 0 && flag_delayed_branch)
-    dbr_schedule (insns);
-
   shorten_branches (insns);
   final_start_function (insns, file, 1);
   final (insns, file, 1);
