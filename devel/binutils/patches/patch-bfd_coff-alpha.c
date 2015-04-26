$NetBSD$

--- bfd/coff-alpha.c.orig	Fri Jul 13 14:22:42 2012
+++ bfd/coff-alpha.c
@@ -642,7 +642,9 @@ alpha_adjust_reloc_in (bfd *abfd,
     case ALPHA_R_OP_STORE:
       /* The STORE reloc needs the size and offset fields.  We store
 	 them in the addend.  */
+#if 0
       BFD_ASSERT (intern->r_offset <= 256);
+#endif
       rptr->addend = (intern->r_offset << 8) + intern->r_size;
       break;
 
