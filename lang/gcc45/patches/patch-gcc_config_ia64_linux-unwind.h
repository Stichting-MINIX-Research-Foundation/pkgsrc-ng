$NetBSD$

--- gcc/config/ia64/linux-unwind.h.orig	Fri Aug 14 20:49:40 2009
+++ gcc/config/ia64/linux-unwind.h
@@ -1,5 +1,5 @@
 /* DWARF2 EH unwinding support for IA64 Linux.
-   Copyright (C) 2004, 2005, 2009 Free Software Foundation, Inc.
+   Copyright (C) 2004, 2005, 2009, 2012 Free Software Foundation, Inc.
 
    This file is part of GCC.
 
@@ -47,7 +47,7 @@ ia64_fallback_frame_state (struct _Unwind_Context *con
       struct sigframe {
 	char scratch[16];
 	unsigned long sig_number;
-	struct siginfo *info;
+	siginfo_t *info;
 	struct sigcontext *sc;
       } *frame_ = (struct sigframe *)context->psp;
       struct sigcontext *sc = frame_->sc;
@@ -137,7 +137,7 @@ ia64_handle_unwabi (struct _Unwind_Context *context, _
       struct sigframe {
 	char scratch[16];
 	unsigned long sig_number;
-	struct siginfo *info;
+	siginfo_t *info;
 	struct sigcontext *sc;
       } *frame = (struct sigframe *)context->psp;
       struct sigcontext *sc = frame->sc;
