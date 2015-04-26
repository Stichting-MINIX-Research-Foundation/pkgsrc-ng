$NetBSD$

--- include/objalloc.h.orig	Tue May 10 10:21:08 2005
+++ include/objalloc.h
@@ -1,5 +1,5 @@
 /* objalloc.h -- routines to allocate memory for objects
-   Copyright 1997, 2001 Free Software Foundation, Inc.
+   Copyright 1997-2012 Free Software Foundation, Inc.
    Written by Ian Lance Taylor, Cygnus Solutions.
 
 This program is free software; you can redistribute it and/or modify it
@@ -91,7 +91,7 @@ extern void *_objalloc_alloc (struct objalloc *, unsig
      if (__len == 0)							\
        __len = 1;							\
      __len = (__len + OBJALLOC_ALIGN - 1) &~ (OBJALLOC_ALIGN - 1);	\
-     (__len <= __o->current_space					\
+     (__len != 0 && __len <= __o->current_space				\
       ? (__o->current_ptr += __len,					\
 	 __o->current_space -= __len,					\
 	 (void *) (__o->current_ptr - __len))				\
