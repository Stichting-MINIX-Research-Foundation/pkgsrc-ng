$NetBSD$

--- gcc/config/xtensa/linux-unwind.h.orig	Thu Apr  9 15:00:19 2009
+++ gcc/config/xtensa/linux-unwind.h
@@ -1,5 +1,5 @@
 /* DWARF2 EH unwinding support for Xtensa.
-   Copyright (C) 2008, 2009 Free Software Foundation, Inc.
+   Copyright (C) 2008, 2009, 2012 Free Software Foundation, Inc.
 
 This file is part of GCC.
 
@@ -62,7 +62,7 @@ xtensa_fallback_frame_state (struct _Unwind_Context *c
   struct sigcontext *sc;
 
   struct rt_sigframe {
-    struct siginfo info;
+    siginfo_t info;
     struct ucontext uc;
   } *rt_;
 
