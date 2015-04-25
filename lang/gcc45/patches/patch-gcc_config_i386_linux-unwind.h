$NetBSD$

--- gcc/config/i386/linux-unwind.h.orig	Fri Nov 13 06:58:12 2009
+++ gcc/config/i386/linux-unwind.h
@@ -1,5 +1,5 @@
 /* DWARF2 EH unwinding support for AMD x86-64 and x86.
-   Copyright (C) 2004, 2005, 2006, 2009 Free Software Foundation, Inc.
+   Copyright (C) 2004, 2005, 2006, 2009, 2012 Free Software Foundation, Inc.
 
 This file is part of GCC.
 
@@ -133,9 +133,9 @@ x86_fallback_frame_state (struct _Unwind_Context *cont
     {
       struct rt_sigframe {
 	int sig;
-	struct siginfo *pinfo;
+	siginfo_t *pinfo;
 	void *puc;
-	struct siginfo info;
+	siginfo_t info;
 	struct ucontext uc;
       } *rt_ = context->cfa;
       /* The void * cast is necessary to avoid an aliasing warning.
