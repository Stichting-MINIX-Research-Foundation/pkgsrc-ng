$NetBSD$

--- libiberty/objalloc.c.orig	Fri Jul 22 03:26:05 2005
+++ libiberty/objalloc.c
@@ -1,5 +1,5 @@
 /* objalloc.c -- routines to allocate memory for objects
-   Copyright 1997 Free Software Foundation, Inc.
+   Copyright 1997-2012 Free Software Foundation, Inc.
    Written by Ian Lance Taylor, Cygnus Solutions.
 
 This program is free software; you can redistribute it and/or modify it
@@ -112,14 +112,21 @@ objalloc_create (void)
 /* Allocate space from an objalloc structure.  */
 
 PTR
-_objalloc_alloc (struct objalloc *o, unsigned long len)
+_objalloc_alloc (struct objalloc *o, unsigned long original_len)
 {
+  unsigned long len = original_len;
+
   /* We avoid confusion from zero sized objects by always allocating
      at least 1 byte.  */
   if (len == 0)
     len = 1;
 
   len = (len + OBJALLOC_ALIGN - 1) &~ (OBJALLOC_ALIGN - 1);
+
+  /* Check for overflow in the alignment operation above and the
+     malloc argument below. */
+  if (len + CHUNK_HEADER_SIZE < original_len)
+    return NULL;
 
   if (len <= o->current_space)
     {
