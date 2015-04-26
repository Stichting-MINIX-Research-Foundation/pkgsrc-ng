$NetBSD$

--- bfd/elf64-alpha.c.orig	Tue Jul 24 21:06:58 2012
+++ bfd/elf64-alpha.c
@@ -100,6 +100,11 @@ bfd_boolean elf64_alpha_use_secureplt = FALSE;
 #define PLT_ENTRY_SIZE \
   (elf64_alpha_use_secureplt ? NEW_PLT_ENTRY_SIZE : OLD_PLT_ENTRY_SIZE)
 
+/* ld --traditional-format uses this older format instead. */
+#define OLD_PLT_ENTRY_WORD1	0x279f0000	/* ldah $28, 0($31) */
+#define OLD_PLT_ENTRY_WORD2	0x239c0000	/* lda  $28, 0($28) */
+#define OLD_PLT_ENTRY_WORD3	0xc3e00000	/* br   $31, plt0   */
+
 #define MAX_GOT_SIZE		(64*1024)
 
 #define ELF_DYNAMIC_INTERPRETER "/usr/lib/ld.so"
@@ -4820,6 +4825,32 @@ elf64_alpha_finish_dynamic_symbol (bfd *output_bfd, st
 
 		plt_index = ((gotent->plt_offset - NEW_PLT_HEADER_SIZE)
 			     / NEW_PLT_ENTRY_SIZE);
+	      }
+	    else if ((output_bfd->flags & BFD_TRADITIONAL_FORMAT) != 0)
+	      {
+	        long hi, lo;
+
+	        /* decompose the reloc offset for the plt for ldah+lda */
+	        hi = plt_index * sizeof(Elf64_External_Rela);
+	        lo = ((hi & 0xffff) ^ 0x8000) - 0x8000;
+	        hi = (hi - lo) >> 16;
+
+	        insn = INSN_ABO (INSN_LDAH, 28, 31, hi);
+		bfd_put_32 (output_bfd, insn,
+			    splt->contents + gotent->plt_offset);
+
+	        insn = INSN_ABO (INSN_LDA, 28, 28, lo);
+		bfd_put_32 (output_bfd, insn,
+			    splt->contents + gotent->plt_offset + 4);
+
+		disp = -(gotent->plt_offset + 12);
+		insn = INSN_AD (INSN_BR, 31, disp);
+
+		bfd_put_32 (output_bfd, insn,
+			    splt->contents + gotent->plt_offset + 8);
+
+		plt_index = ((gotent->plt_offset - OLD_PLT_HEADER_SIZE)
+			     / OLD_PLT_ENTRY_SIZE);
 	      }
 	    else
 	      {
