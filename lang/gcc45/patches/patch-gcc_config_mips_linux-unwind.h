$NetBSD$

--- gcc/config/mips/linux-unwind.h.orig	Thu Apr  9 15:00:19 2009
+++ gcc/config/mips/linux-unwind.h
@@ -1,5 +1,6 @@
 /* DWARF2 EH unwinding support for MIPS Linux.
-   Copyright (C) 2004, 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
+   Copyright (C) 2004, 2005, 2006, 2007, 2008, 2009, 2012 Free Software
+   Foundation, Inc.
 
 This file is part of GCC.
 
@@ -75,7 +76,7 @@ mips_fallback_frame_state (struct _Unwind_Context *con
       struct rt_sigframe {
 	u_int32_t ass[4];  /* Argument save space for o32.  */
 	u_int32_t trampoline[2];
-	struct siginfo info;
+	siginfo_t info;
 	_sig_ucontext_t uc;
       } *rt_ = context->cfa;
       sc = &rt_->uc.uc_mcontext;
