$NetBSD$

--- bfd/elf64-x86-64.c.orig	Mon Mar 25 08:06:20 2013
+++ bfd/elf64-x86-64.c
@@ -2589,6 +2589,10 @@ elf_x86_64_readonly_dynrelocs (struct elf_link_hash_en
 	{
 	  struct bfd_link_info *info = (struct bfd_link_info *) inf;
 
+          if (info->warn_shared_textrel)
+            (*_bfd_error_handler)
+              (_("warning: dynamic relocation in readonly section `%s'"),
+              h->root.root.string);
 	  info->flags |= DF_TEXTREL;
 
 	  if (info->warn_shared_textrel && info->shared)
