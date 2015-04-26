$NetBSD$

--- bfd/elf32-ppc.c.orig	Mon Mar 25 08:06:19 2013
+++ bfd/elf32-ppc.c
@@ -3898,7 +3898,7 @@ ppc_elf_check_relocs (bfd *abfd,
 	    sec->has_tls_get_addr_call = 1;
 	}
 
-      switch (r_type)
+      switch ((int)r_type)
 	{
 	case R_PPC_TLSGD:
 	case R_PPC_TLSLD:
@@ -7766,7 +7766,7 @@ ppc_elf_relocate_section (bfd *output_bfd,
       howto = NULL;
       if (r_type < R_PPC_max)
 	howto = ppc_elf_howto_table[r_type];
-      switch (r_type)
+      switch ((int)r_type)
 	{
 	default:
 	  info->callbacks->einfo
