$NetBSD$

--- include/bfdlink.h.orig	Mon Apr  9 16:27:18 2012
+++ include/bfdlink.h
@@ -435,6 +435,10 @@ struct bfd_link_info
      option).  If this is NULL, no symbols are being wrapped.  */
   struct bfd_hash_table *wrap_hash;
 
+  /* Hash table of symbols which may be left unresolved during
+     a link.  If this is NULL, no symbols can be left unresolved.  */
+  struct bfd_hash_table *ignore_hash;
+
   /* The output BFD.  */
   bfd *output_bfd;
 
