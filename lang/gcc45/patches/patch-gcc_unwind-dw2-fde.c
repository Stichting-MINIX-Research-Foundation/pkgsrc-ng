$NetBSD$

--- gcc/unwind-dw2-fde.c.orig	Sun Sep 20 11:03:33 2009
+++ gcc/unwind-dw2-fde.c
@@ -209,7 +209,9 @@ __deregister_frame_info_bases (const void *begin)
 
  out:
   __gthread_mutex_unlock (&object_mutex);
+#if 0
   gcc_assert (ob);
+#endif
   return (void *) ob;
 }
 
