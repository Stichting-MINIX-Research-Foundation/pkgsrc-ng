$NetBSD$

--- gcc/config/sh/linux-unwind.h.orig	Thu Apr  9 15:00:19 2009
+++ gcc/config/sh/linux-unwind.h
@@ -1,5 +1,6 @@
 /* DWARF2 EH unwinding support for SH Linux.
-   Copyright (C) 2004, 2005, 2006, 2007, 2009 Free Software Foundation, Inc.
+   Copyright (C) 2004, 2005, 2006, 2007, 2009, 2012 Free Software Foundation,
+   Inc.
 
 This file is part of GCC.
 
@@ -80,9 +81,9 @@ shmedia_fallback_frame_state (struct _Unwind_Context *
 	   && (*(unsigned long *) (pc+11)  == 0x6ff0fff0))
     {
       struct rt_sigframe {
-	struct siginfo *pinfo;
+	siginfo_t *pinfo;
 	void *puc;
-	struct siginfo info;
+	siginfo_t info;
 	struct ucontext uc;
       } *rt_ = context->cfa;
       /* The void * cast is necessary to avoid an aliasing warning.
@@ -179,7 +180,7 @@ sh_fallback_frame_state (struct _Unwind_Context *conte
 		&& (*(unsigned short *) (pc+14)  == 0x00ad))))
     {
       struct rt_sigframe {
-	struct siginfo info;
+	siginfo_t info;
 	struct ucontext uc;
       } *rt_ = context->cfa;
       /* The void * cast is necessary to avoid an aliasing warning.
