$NetBSD$

--- gcc/config/bfin/linux-unwind.h.orig	Thu Apr  9 15:00:19 2009
+++ gcc/config/bfin/linux-unwind.h
@@ -1,5 +1,5 @@
 /* DWARF2 EH unwinding support for Blackfin.
-   Copyright (C) 2007, 2009 Free Software Foundation, Inc.
+   Copyright (C) 2007, 2009, 2012 Free Software Foundation, Inc.
 
 This file is part of GCC.
 
@@ -48,10 +48,10 @@ bfin_fallback_frame_state (struct _Unwind_Context *con
     {
       struct rt_sigframe {
 	int sig;
-	struct siginfo *pinfo;
+	siginfo_t *pinfo;
 	void *puc;
 	char retcode[8];
-	struct siginfo info;
+	siginfo_t info;
 	struct ucontext uc;
       } *rt_ = context->cfa;
 
