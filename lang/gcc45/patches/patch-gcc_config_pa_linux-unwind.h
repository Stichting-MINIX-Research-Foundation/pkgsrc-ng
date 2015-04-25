$NetBSD$

--- gcc/config/pa/linux-unwind.h.orig	Sat Dec  5 17:45:59 2009
+++ gcc/config/pa/linux-unwind.h
@@ -1,5 +1,5 @@
 /* DWARF2 EH unwinding support for PA Linux.
-   Copyright (C) 2004, 2005, 2009 Free Software Foundation, Inc.
+   Copyright (C) 2004, 2005, 2009, 2012 Free Software Foundation, Inc.
 
 This file is part of GCC.
 
@@ -63,7 +63,7 @@ pa32_fallback_frame_state (struct _Unwind_Context *con
   int i;
   struct sigcontext *sc;
   struct rt_sigframe {
-    struct siginfo info;
+    siginfo_t info;
     struct ucontext uc;
   } *frame;
 
