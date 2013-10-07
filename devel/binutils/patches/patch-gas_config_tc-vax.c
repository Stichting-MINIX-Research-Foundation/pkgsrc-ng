$NetBSD$

--- gas/config/tc-vax.c.orig	Mon Jun 28 14:06:57 2010
+++ gas/config/tc-vax.c
@@ -392,6 +392,9 @@ md_estimate_size_before_relax (fragS *fragP, segT segm
 	      && (PLT_symbol == NULL || fragP->fr_symbol != PLT_symbol)
 	      && fragP->fr_symbol != NULL
 	      && flag_want_pic
+#ifdef OBJ_ELF
+	      && ELF_ST_VISIBILITY (S_GET_OTHER (fragP->fr_symbol)) != STV_HIDDEN
+#endif
 	      && (!S_IS_DEFINED (fragP->fr_symbol)
 	          || S_IS_WEAK (fragP->fr_symbol)
 	          || S_IS_EXTERNAL (fragP->fr_symbol)))
@@ -1073,6 +1076,154 @@ vax_reg_parse (char c1, char c2, char c3, char c4)
   return retval;
 }
 
+#ifdef OBJ_AOUT
+#ifndef BFD_ASSEMBLER
+void
+tc_aout_fix_to_chars (where, fixP, segment_address_in_file)
+     char *where;
+     fixS *fixP;
+     relax_addressT segment_address_in_file;
+{
+  /*
+   * In: length of relocation (or of address) in chars: 1, 2 or 4.
+   * Out: GNU LD relocation length code: 0, 1, or 2.
+   */
+
+  static const unsigned char nbytes_r_length[] = {42, 0, 1, 42, 2};
+  int r_symbolnum;
+  int r_flags;
+
+  know (fixP->fx_addsy != NULL);
+
+  md_number_to_chars (where,
+       fixP->fx_frag->fr_address + fixP->fx_where - segment_address_in_file,
+		      4);
+
+  r_symbolnum = (S_IS_DEFINED (fixP->fx_addsy)
+		 ? S_GET_TYPE (fixP->fx_addsy)
+		 : fixP->fx_addsy->sy_number);
+  r_flags = (fixP->fx_pcrel ? 1 : 0)
+      | (!S_IS_DEFINED (fixP->fx_addsy) ? 8 : 0)	/* extern */
+      | ((nbytes_r_length[fixP->fx_size] & 3) << 1);
+
+#if 0
+  r_flags |= ((!S_IS_DEFINED(fixP->fx_addsy)
+      && fixP->fx_pcrel
+      && fixP->fx_addsy != GOT_symbol
+      && fixP->fx_addsy != PLT_symbol
+      && flags_want_pic) ? 0x10 : 0);
+#endif
+	
+  switch (fixP->fx_r_type) {
+	case NO_RELOC:
+		break;
+	case NO_RELOC2:
+		if (r_flags & 8)
+		    r_flags |= 0x80;		/* setting the copy bit */
+						/*   says we can convert */
+						/*   to gotslot if needed */
+		break;
+	case RELOC_32:
+		if (flag_want_pic && S_IS_EXTERNAL(fixP->fx_addsy)) {
+			r_symbolnum = fixP->fx_addsy->sy_number;  
+			r_flags |= 8;		/* set extern bit */
+		}
+		break;
+	case RELOC_JMP_SLOT:
+		if (flag_want_pic) {
+			r_flags |= 0x20;	/* set jmptable */
+			r_flags &= ~0x08;	/* clear extern bit */
+		}
+		break;
+	case RELOC_JMP_TBL:
+		if (flag_want_pic) {
+			r_flags |= 0x20;	/* set jmptable */
+			r_flags |= 0x08;	/* set extern bit */
+		}
+		break;
+	case RELOC_GLOB_DAT:
+		if (flag_want_pic) {
+			r_flags |= 0x10;	/* set baserel bit */
+			r_symbolnum = fixP->fx_addsy->sy_number;
+			if (S_IS_EXTERNAL(fixP->fx_addsy))
+				r_flags |= 8;	/* set extern bit */
+		}
+		break;
+  }
+
+  where[4] = (r_symbolnum >>  0) & 0xff;
+  where[5] = (r_symbolnum >>  8) & 0xff;
+  where[6] = (r_symbolnum >> 16) & 0xff;
+  where[7] = r_flags;
+}
+#endif /* !BFD_ASSEMBLER */
+#endif /* OBJ_AOUT */
+
+/*
+ *       BUGS, GRIPES,  APOLOGIA, etc.
+ *
+ * The opcode table 'votstrs' needs to be sorted on opcode frequency.
+ * That is, AFTER we hash it with hash_...(), we want most-used opcodes
+ * to come out of the hash table faster.
+ *
+ * I am sorry to inflict yet another VAX assembler on the world, but
+ * RMS says we must do everything from scratch, to prevent pin-heads
+ * restricting this software.
+ */
+
+/*
+ * This is a vaguely modular set of routines in C to parse VAX
+ * assembly code using DEC mnemonics. It is NOT un*x specific.
+ *
+ * The idea here is that the assembler has taken care of all:
+ *   labels
+ *   macros
+ *   listing
+ *   pseudo-ops
+ *   line continuation
+ *   comments
+ *   condensing any whitespace down to exactly one space
+ * and all we have to do is parse 1 line into a vax instruction
+ * partially formed. We will accept a line, and deliver:
+ *   an error message (hopefully empty)
+ *   a skeleton VAX instruction (tree structure)
+ *   textual pointers to all the operand expressions
+ *   a warning message that notes a silly operand (hopefully empty)
+ */
+
+/*
+ *		E D I T   H I S T O R Y
+ *
+ * 17may86 Dean Elsner. Bug if line ends immediately after opcode.
+ * 30apr86 Dean Elsner. New vip_op() uses arg block so change call.
+ *  6jan86 Dean Elsner. Crock vip_begin() to call vip_op_defaults().
+ *  2jan86 Dean Elsner. Invent synthetic opcodes.
+ *	Widen vax_opcodeT to 32 bits. Use a bit for VIT_OPCODE_SYNTHETIC,
+ *	which means this is not a real opcode, it is like a macro; it will
+ *	be relax()ed into 1 or more instructions.
+ *	Use another bit for VIT_OPCODE_SPECIAL if the op-code is not optimised
+ *	like a regular branch instruction. Option added to vip_begin():
+ *	exclude	synthetic opcodes. Invent synthetic_votstrs[].
+ * 31dec85 Dean Elsner. Invent vit_opcode_nbytes.
+ *	Also make vit_opcode into a char[]. We now have n-byte vax opcodes,
+ *	so caller's don't have to know the difference between a 1-byte & a
+ *	2-byte op-code. Still need vax_opcodeT concept, so we know how
+ *	big an object must be to hold an op.code.
+ * 30dec85 Dean Elsner. Widen typedef vax_opcodeT in "vax-inst.h"
+ *	because vax opcodes may be 16 bits. Our crufty C compiler was
+ *	happily initialising 8-bit vot_codes with 16-bit numbers!
+ *	(Wouldn't the 'phone company like to compress data so easily!)
+ * 29dec85 Dean Elsner. New static table vax_operand_width_size[].
+ *	Invented so we know hw many bytes a "I^#42" needs in its immediate
+ *	operand. Revised struct vop in "vax-inst.h": explicitly include
+ *	byte length of each operand, and it's letter-code datum type.
+ * 17nov85 Dean Elsner. Name Change.
+ *	Due to ar(1) truncating names, we learned the hard way that
+ *	"vax-inst-parse.c" -> "vax-inst-parse." dropping the "o" off
+ *	the archived object name. SO... we shortened the name of this
+ *	source file, and changed the makefile.
+ */
+
 /* Parse a vax operand in DEC assembler notation.
    For speed, expect a string of whitespace to be reduced to a single ' '.
    This is the case for GNU AS, and is easy for other DEC-compatible
@@ -3150,7 +3301,7 @@ md_assemble (char *instruction_string)
 			  if (flag_want_pic && operandP->vop_mode == 8
 				&& this_add_symbol != NULL)
 			    {
-			      as_warn (_("Symbol %s used as immediate operand in PIC mode."),
+			      as_warn (_("Symbol '%s' used as immediate operand in PIC mode."),
 				       S_GET_NAME (this_add_symbol));
 			    }
 #endif
@@ -3226,7 +3377,15 @@ md_assemble (char *instruction_string)
 			      length = 4;
 			    }
 			}
+#ifdef OBJ_ELF
+		      if (flag_want_pic && this_add_symbol != NULL)
+		        {
+			  as_warn (_("Symbol '%s' used as displacement in PIC mode."),
+			       S_GET_NAME (this_add_symbol));
+		        }
+#endif
 		      p = frag_more (1 + length);
+		      know (operandP->vop_reg != 0xf);
 		      know (operandP->vop_reg >= 0);
 		      p[0] = operandP->vop_reg
 			| ((at | "?\12\14?\16"[length]) << 4);
