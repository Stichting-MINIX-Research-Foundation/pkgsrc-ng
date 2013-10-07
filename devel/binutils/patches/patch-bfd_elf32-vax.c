$NetBSD$

--- bfd/elf32-vax.c.orig	Tue Sep  4 13:32:53 2012
+++ bfd/elf32-vax.c
@@ -490,6 +490,24 @@ elf32_vax_set_private_flags (bfd *abfd, flagword flags
   return TRUE;
 }
 
+/* Copy vax-specific data from one module to another */
+static bfd_boolean
+elf32_vax_copy_private_bfd_data (bfd *ibfd, bfd *obfd)
+{
+  flagword in_flags;
+
+  if (bfd_get_flavour (ibfd) != bfd_target_elf_flavour
+      || bfd_get_flavour (obfd) != bfd_target_elf_flavour)
+    return TRUE;
+ 
+  in_flags = elf_elfheader (ibfd)->e_flags;
+ 
+  elf_elfheader (obfd)->e_flags = in_flags;
+  elf_flags_init (obfd) = TRUE;
+ 
+  return TRUE;
+}
+
 /* Merge backend specific data from an object file to the output
    object file when linking.  */
 static bfd_boolean
@@ -752,7 +770,13 @@ elf_vax_check_relocs (bfd *abfd, struct bfd_link_info 
 		    return FALSE;
 
 		  if (sec->flags & SEC_READONLY)
-		    info->flags |= DF_TEXTREL;
+		    {
+			if (info->warn_shared_textrel)
+			  (*_bfd_error_handler)
+			    (_("warning: dynamic relocation in readonly section `%s'"),
+			     sec->name);
+			info->flags |= DF_TEXTREL;
+		    }
 		}
 
 	      sreloc->size += sizeof (Elf32_External_Rela);
@@ -1186,7 +1210,12 @@ elf_vax_size_dynamic_sections (bfd *output_bfd, struct
 	continue;
 
       /* Allocate memory for the section contents.  */
-      s->contents = (bfd_byte *) bfd_alloc (dynobj, s->size);
+      /* FIXME: This should be a call to bfd_alloc not bfd_zalloc.
+	 Unused entries should be reclaimed before the section's contents
+	 are written out, but at the moment this does not happen.  Thus in
+	 order to prevent writing out garbage, we initialise the section's
+	 contents to zero.  */
+      s->contents = (bfd_byte *) bfd_zalloc (dynobj, s->size);
       if (s->contents == NULL)
 	return FALSE;
     }
@@ -1285,6 +1314,7 @@ elf_vax_instantiate_got_entries (struct elf_link_hash_
 
   if (!elf_hash_table (info)->dynamic_sections_created
       || (info->shared && info->symbolic)
+      || ELF_ST_VISIBILITY (h->other) != STV_DEFAULT
       || h->forced_local)
     {
       h->got.refcount = 0;
@@ -1305,9 +1335,7 @@ elf_vax_instantiate_got_entries (struct elf_link_hash_
 
       dyn = elf_hash_table (info)->dynamic_sections_created;
       /* Allocate space in the .got and .rela.got sections.  */
-      if (ELF_ST_VISIBILITY (h->other) == STV_DEFAULT
-	  && (info->shared
-	      || WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, 0, h)))
+      if (info->shared || WILL_CALL_FINISH_DYNAMIC_SYMBOL (dyn, 0, h))
 	{
 	  sgot->size += 4;
 	  srelgot->size += sizeof (Elf32_External_Rela);
@@ -1631,9 +1659,9 @@ elf_vax_relocate_section (bfd *output_bfd,
 		    {
 		      relocate = TRUE;
 		      outrel.r_info = ELF32_R_INFO (0, R_VAX_RELATIVE);
-		      BFD_ASSERT (bfd_get_signed_32 (input_bfd,
-						     &contents[rel->r_offset]) == 0);
-		      outrel.r_addend = relocation + rel->r_addend;
+		      outrel.r_addend = bfd_get_signed_32(input_bfd,
+							 &contents[rel->r_offset])
+					+ relocation + rel->r_addend;
 		    }
 		  else
 		    {
@@ -1672,6 +1700,9 @@ elf_vax_relocate_section (bfd *output_bfd,
 		    }
 		}
 
+	      if (input_section->flags & SEC_CODE)
+		 info->flags |= DF_TEXTREL;
+
 	      if ((input_section->flags & SEC_CODE) != 0
 		  || (ELF32_R_TYPE (outrel.r_info) != R_VAX_32
 		      && ELF32_R_TYPE (outrel.r_info) != R_VAX_RELATIVE
@@ -2051,12 +2082,15 @@ elf_vax_plt_sym_val (bfd_vma i, const asection *plt,
 #define TARGET_LITTLE_SYM		bfd_elf32_vax_vec
 #define TARGET_LITTLE_NAME		"elf32-vax"
 #define ELF_MACHINE_CODE		EM_VAX
-#define ELF_MAXPAGESIZE			0x1000
+#define ELF_MAXPAGESIZE			0x10000
 
 #define elf_backend_create_dynamic_sections \
 					_bfd_elf_create_dynamic_sections
 #define bfd_elf32_bfd_link_hash_table_create \
 					elf_vax_link_hash_table_create
+#define bfd_elf32_bfd_copy_private_bfd_data \
+					elf32_vax_copy_private_bfd_data
+
 #define bfd_elf32_bfd_final_link	bfd_elf_gc_common_final_link
 
 #define elf_backend_check_relocs	elf_vax_check_relocs
