$NetBSD$

--- bfd/elfxx-sparc.c.orig	Mon Mar 25 08:06:20 2013
+++ bfd/elfxx-sparc.c
@@ -2508,6 +2508,10 @@ readonly_dynrelocs (struct elf_link_hash_entry *h, voi
 	{
 	  struct bfd_link_info *info = (struct bfd_link_info *) inf;
 
+          if (info->warn_shared_textrel)
+            (*_bfd_error_handler)
+              (_("warning: dynamic relocation in readonly section `%s'"),
+              h->root.root.string);
 	  info->flags |= DF_TEXTREL;
 
 	  /* Not an error, just cut short the traversal.  */
@@ -3460,10 +3464,8 @@ _bfd_sparc_elf_relocate_section (bfd *output_bfd,
 		memset (&outrel, 0, sizeof outrel);
 	      /* h->dynindx may be -1 if the symbol was marked to
 		 become local.  */
-	      else if (h != NULL &&
-		       h->dynindx != -1
-		       && (! is_plt
-			   || !info->shared
+	      else if (h != NULL && h->dynindx != -1 && ! is_plt
+		       && (!info->shared
 			   || !SYMBOLIC_BIND (info, h)
 			   || !h->def_regular))
 		{
