$NetBSD$

--- bfd/elf32-hppa.c.orig	Fri Jun 29 14:45:58 2012
+++ bfd/elf32-hppa.c
@@ -2191,6 +2191,10 @@ readonly_dynrelocs (struct elf_link_hash_entry *eh, vo
 	{
 	  struct bfd_link_info *info = inf;
 
+          if (info->warn_shared_textrel)
+            (*_bfd_error_handler)
+              (_("warning: dynamic relocation in readonly section `%s'"),
+              eh->root.root.string);
 	  info->flags |= DF_TEXTREL;
 
 	  /* Not an error, just cut short the traversal.  */
