$NetBSD$

--- gcc/config/alpha/linux-unwind.h.orig	Thu Apr  9 15:00:19 2009
+++ gcc/config/alpha/linux-unwind.h
@@ -1,5 +1,5 @@
 /* DWARF2 EH unwinding support for Alpha Linux.
-   Copyright (C) 2004, 2005, 2009 Free Software Foundation, Inc.
+   Copyright (C) 2004, 2005, 2009, 2011, 2012 Free Software Foundation, Inc.
 
 This file is part of GCC.
 
@@ -36,25 +36,27 @@ alpha_fallback_frame_state (struct _Unwind_Context *co
 {
   unsigned int *pc = context->ra;
   struct sigcontext *sc;
-  long new_cfa, i;
+  long new_cfa;
+  int i;
 
   if (pc[0] != 0x47fe0410		/* mov $30,$16 */
-      || pc[2] != 0x00000083		/* callsys */)
+      || pc[2] != 0x00000083)		/* callsys */
     return _URC_END_OF_STACK;
   if (context->cfa == 0)
     return _URC_END_OF_STACK;
   if (pc[1] == 0x201f0067)		/* lda $0,NR_sigreturn */
     sc = context->cfa;
-  else if (pc[1] == 0x201f015f)	/* lda $0,NR_rt_sigreturn */
+  else if (pc[1] == 0x201f015f)		/* lda $0,NR_rt_sigreturn */
     {
       struct rt_sigframe {
-	struct siginfo info;
+	siginfo_t info;
 	struct ucontext uc;
       } *rt_ = context->cfa;
       sc = &rt_->uc.uc_mcontext;
     }
   else
     return _URC_END_OF_STACK;
+
   new_cfa = sc->sc_regs[30];
   fs->regs.cfa_how = CFA_REG_OFFSET;
   fs->regs.cfa_reg = 30;
@@ -63,16 +65,35 @@ alpha_fallback_frame_state (struct _Unwind_Context *co
     {
       fs->regs.reg[i].how = REG_SAVED_OFFSET;
       fs->regs.reg[i].loc.offset
-	= (long)&sc->sc_regs[i] - new_cfa;
+	= (long) &sc->sc_regs[i] - new_cfa;
     }
   for (i = 0; i < 31; ++i)
     {
       fs->regs.reg[i+32].how = REG_SAVED_OFFSET;
       fs->regs.reg[i+32].loc.offset
-	= (long)&sc->sc_fpregs[i] - new_cfa;
+	= (long) &sc->sc_fpregs[i] - new_cfa;
     }
   fs->regs.reg[64].how = REG_SAVED_OFFSET;
   fs->regs.reg[64].loc.offset = (long)&sc->sc_pc - new_cfa;
   fs->retaddr_column = 64;
+  fs->signal_frame = 1;
+
   return _URC_NO_REASON;
+}
+
+#define MD_FROB_UPDATE_CONTEXT alpha_frob_update_context
+
+/* Fix up for signal handlers that don't have S flag set.  */
+
+static void
+alpha_frob_update_context (struct _Unwind_Context *context,
+			   _Unwind_FrameState *fs ATTRIBUTE_UNUSED)
+{
+  unsigned int *pc = context->ra;
+
+  if (pc[0] == 0x47fe0410		/* mov $30,$16 */
+      && pc[2] == 0x00000083		/* callsys */
+      && (pc[1] == 0x201f0067		/* lda $0,NR_sigreturn */
+	  || pc[1] == 0x201f015f))	/* lda $0,NR_rt_sigreturn */
+    _Unwind_SetSignalFrame (context, 1);
 }
