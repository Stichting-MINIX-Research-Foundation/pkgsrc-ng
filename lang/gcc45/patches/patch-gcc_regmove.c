$NetBSD$

--- gcc/regmove.c.orig	Sun Jan 16 20:16:30 2011
+++ gcc/regmove.c
@@ -859,7 +859,7 @@ fixup_match_2 (rtx insn, rtx dst, rtx src, rtx offset)
 	  if (REG_N_CALLS_CROSSED (REGNO (src)) == 0)
 	    break;
 
-	  if (call_used_regs [REGNO (dst)]
+	  if ((HARD_REGISTER_P (dst) && call_used_regs [REGNO (dst)])
 	      || find_reg_fusage (p, CLOBBER, dst))
 	    break;
 	}
