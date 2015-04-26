$NetBSD$

--- bfd/elf32-arm.c.orig	Mon Mar 25 08:06:19 2013
+++ bfd/elf32-arm.c
@@ -13475,6 +13475,10 @@ elf32_arm_readonly_dynrelocs (struct elf_link_hash_ent
 	{
 	  struct bfd_link_info *info = (struct bfd_link_info *) inf;
 
+          if (info->warn_shared_textrel)
+            (*_bfd_error_handler)
+              (_("warning: dynamic relocation in readonly section `%s'"),
+              h->root.root.string);
 	  info->flags |= DF_TEXTREL;
 
 	  /* Not an error, just cut short the traversal.  */
