$NetBSD$

--- bfd/elfxx-mips.c.orig	Mon Mar 25 08:06:20 2013
+++ bfd/elfxx-mips.c
@@ -8191,10 +8191,24 @@ _bfd_mips_elf_check_relocs (bfd *abfd, struct bfd_link
 		     reloc types into the output file as R_MIPS_REL32
 		     relocs.  Make room for this reloc in .rel(a).dyn.  */
 		  mips_elf_allocate_dynamic_relocations (dynobj, info, 1);
-		  if (MIPS_ELF_READONLY_SECTION (sec))
-		    /* We tell the dynamic linker that there are
-		       relocations against the text segment.  */
-		    info->flags |= DF_TEXTREL;
+		  /* In the N32 and 64-bit ABIs there may be multiple
+		     consecutive relocations for the same offset.  If we have
+		     a R_MIPS_GPREL32 followed by a R_MIPS_64 then that
+		     relocation is complete and needs no futher adjustment.  */
+		  if ((rel == relocs
+		      || rel[-1].r_offset != rel->r_offset
+		      || r_type != R_MIPS_64
+		      || ELF_R_TYPE(abfd, rel[-1].r_info) != R_MIPS_GPREL32)
+		      && MIPS_ELF_READONLY_SECTION (sec))
+		    {
+		      /* We tell the dynamic linker that there are
+		         relocations against the text segment.  */
+		      info->flags |= DF_TEXTREL;
+		      info->callbacks->warning
+			(info,
+			 _("relocation emitted against readonly section"),
+			 NULL, abfd, sec, rel->r_offset);
+		    }
 		}
 	      else
 		{
