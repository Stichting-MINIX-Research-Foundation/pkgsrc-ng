$NetBSD$

--- bfd/elf32-m68k.c.orig	Fri Jul 13 14:22:47 2012
+++ bfd/elf32-m68k.c
@@ -2532,7 +2532,7 @@ elf_m68k_copy_indirect_symbol (struct bfd_link_info *i
   if (ind->got_entry_key != 0)
     {
       BFD_ASSERT (dir->got_entry_key == 0);
-      /* Assert that GOTs aren't partioned yet.  */
+      /* Assert that GOTs aren't partitioned yet.  */
       BFD_ASSERT (ind->glist == NULL);
 
       dir->got_entry_key = ind->got_entry_key;
