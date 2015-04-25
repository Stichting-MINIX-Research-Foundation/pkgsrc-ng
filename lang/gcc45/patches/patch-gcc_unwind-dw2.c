$NetBSD$

--- gcc/unwind-dw2.c.orig	Tue Apr 27 09:41:30 2010
+++ gcc/unwind-dw2.c
@@ -1076,12 +1076,14 @@ execute_cfa_program (const unsigned char *insn_ptr,
 	  break;
 
 	case DW_CFA_GNU_window_save:
+#ifdef __sparc__
 	  /* ??? Hardcoded for SPARC register window configuration.  */
 	  for (reg = 16; reg < 32; ++reg)
 	    {
 	      fs->regs.reg[reg].how = REG_SAVED_OFFSET;
 	      fs->regs.reg[reg].loc.offset = (reg - 16) * sizeof (void *);
 	    }
+#endif
 	  break;
 
 	case DW_CFA_GNU_args_size:
