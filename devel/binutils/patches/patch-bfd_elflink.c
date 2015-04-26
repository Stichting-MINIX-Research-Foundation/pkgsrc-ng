$NetBSD$

--- bfd/elflink.c.orig	Mon Mar 25 08:06:20 2013
+++ bfd/elflink.c
@@ -10183,7 +10183,14 @@ elf_reloc_link_order (bfd *output_bfd,
   if (bed->s->arch_size == 32)
     irel[0].r_info = ELF32_R_INFO (indx, howto->type);
   else
-    irel[0].r_info = ELF64_R_INFO (indx, howto->type);
+#ifdef BFD64
+          {
+            bfd_uint64_t indx64 = indx;
+            irel[0].r_info = ELF64_R_INFO (indx64, howto->type);
+          }
+#else
+          BFD_FAIL();
+#endif
 
   rel_hdr = reldata->hdr;
   erel = rel_hdr->contents;
