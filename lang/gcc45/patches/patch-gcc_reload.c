$NetBSD$

--- gcc/reload.c.orig	Mon Dec 21 16:32:44 2009
+++ gcc/reload.c
@@ -6795,6 +6795,15 @@ find_equiv_reg (rtx goal, rtx insn, enum reg_class rcl
 	  || num > PARAM_VALUE (PARAM_MAX_RELOAD_SEARCH_INSNS))
 	return 0;
 
+      /* Don't reuse register contents from before a setjmp-type
+	 function call; on the second return (from the longjmp) it
+	 might have been clobbered by a later reuse.  It doesn't
+	 seem worthwhile to actually go and see if it is actually
+	 reused even if that information would be readily available;
+	 just don't reuse it across the setjmp call.  */
+      if (CALL_P (p) && find_reg_note (p, REG_SETJMP, NULL_RTX))
+	return 0;
+
       if (NONJUMP_INSN_P (p)
 	  /* If we don't want spill regs ...  */
 	  && (! (reload_reg_p != 0
