$NetBSD$

--- gcc/config/sparc/sparc.c.orig	Mon Jan  3 12:06:19 2011
+++ gcc/config/sparc/sparc.c
@@ -627,6 +627,17 @@ sparc_handle_option (size_t code, const char *arg, int
   return true;
 }
 
+/* Specify default optimizations.  */
+
+void
+sparc_optimization_options (int l ATTRIBUTE_UNUSED, int s ATTRIBUTE_UNUSED)
+{
+  /* Disable save slot sharing for call-clobbered registers by default.
+     The IRA sharing algorithm works on single registers only and this
+     pessimizes for double floating-point registers.  */
+  flag_ira_share_save_slots = 0;
+}
+
 /* Validate and override various options, and do some machine dependent
    initialization.  */
 
@@ -2767,11 +2778,6 @@ eligible_for_return_delay (rtx trial)
   if (get_attr_length (trial) != 1)
     return 0;
 
-  /* If there are any call-saved registers, we should scan TRIAL if it
-     does not reference them.  For now just make it easy.  */
-  if (num_gfregs)
-    return 0;
-
   /* If the function uses __builtin_eh_return, the eh_return machinery
      occupies the delay slot.  */
   if (crtl->calls_eh_return)
@@ -4093,7 +4099,7 @@ save_or_restore_regs (int low, int high, rtx base, int
 	    emit_move_insn (gen_rtx_REG (mode, regno), mem);
 
 	  /* Always preserve double-word alignment.  */
-	  offset = (offset + 7) & -8;
+	  offset = (offset + 8) & -8;
 	}
     }
 
@@ -4200,7 +4206,7 @@ sparc_expand_prologue (void)
      example, the regrename pass has special provisions to not rename to
      non-leaf registers in a leaf function.  */
   sparc_leaf_function_p
-    = optimize > 0 && leaf_function_p () && only_leaf_regs_used ();
+    = optimize > 0 && current_function_is_leaf && only_leaf_regs_used ();
 
   /* Need to use actual_fsize, since we are also allocating
      space for our callee (and our own register save area).  */
@@ -4230,8 +4236,9 @@ sparc_expand_prologue (void)
       else if (actual_fsize <= 8192)
 	{
 	  insn = emit_insn (gen_stack_pointer_inc (GEN_INT (-4096)));
-	  /* %sp is still the CFA register.  */
 	  RTX_FRAME_RELATED_P (insn) = 1;
+
+	  /* %sp is still the CFA register.  */
 	  insn
 	    = emit_insn (gen_stack_pointer_inc (GEN_INT (4096-actual_fsize)));
 	}
@@ -4253,8 +4260,18 @@ sparc_expand_prologue (void)
       else if (actual_fsize <= 8192)
 	{
 	  insn = emit_insn (gen_save_register_window (GEN_INT (-4096)));
+
 	  /* %sp is not the CFA register anymore.  */
 	  emit_insn (gen_stack_pointer_inc (GEN_INT (4096-actual_fsize)));
+
+	  /* Make sure no %fp-based store is issued until after the frame is
+	     established.  The offset between the frame pointer and the stack
+	     pointer is calculated relative to the value of the stack pointer
+	     at the end of the function prologue, and moving instructions that
+	     access the stack via the frame pointer between the instructions
+	     that decrement the stack pointer could result in accessing the
+	     register window save area, which is volatile.  */
+	  emit_insn (gen_frame_blockage ());
 	}
       else
 	{
@@ -4324,6 +4341,7 @@ bool
 sparc_can_use_return_insn_p (void)
 {
   return sparc_prologue_data_valid_p
+	 && num_gfregs == 0
 	 && (actual_fsize == 0 || !sparc_leaf_function_p);
 }
 
@@ -4425,18 +4443,20 @@ output_return (rtx insn)
 	     machinery occupies the delay slot.  */
 	  gcc_assert (! final_sequence);
 
-	  if (! flag_delayed_branch)
-	    fputs ("\tadd\t%fp, %g1, %fp\n", asm_out_file);
+          if (flag_delayed_branch)
+	    {
+	      if (TARGET_V9)
+		fputs ("\treturn\t%i7+8\n", asm_out_file);
+	      else
+		fputs ("\trestore\n\tjmp\t%o7+8\n", asm_out_file);
 
-	  if (TARGET_V9)
-	    fputs ("\treturn\t%i7+8\n", asm_out_file);
+	      fputs ("\t add\t%sp, %g1, %sp\n", asm_out_file);
+	    }
 	  else
-	    fputs ("\trestore\n\tjmp\t%o7+8\n", asm_out_file);
-
-	  if (flag_delayed_branch)
-	    fputs ("\t add\t%sp, %g1, %sp\n", asm_out_file);
-	  else
-	    fputs ("\t nop\n", asm_out_file);
+	    {
+	      fputs ("\trestore\n\tadd\t%sp, %g1, %sp\n", asm_out_file);
+	      fputs ("\tjmp\t%o7+8\n\t nop\n", asm_out_file);
+	    }
 	}
       else if (final_sequence)
 	{
@@ -9104,6 +9124,7 @@ sparc_file_end (void)
 						       void_list_node));
 	  DECL_RESULT (decl) = build_decl (BUILTINS_LOCATION, RESULT_DECL,
 					   NULL_TREE, void_type_node);
+	  TREE_PUBLIC (decl) = 1;
 	  TREE_STATIC (decl) = 1;
 	  make_decl_one_only (decl, DECL_ASSEMBLER_NAME (decl));
 	  DECL_VISIBILITY (decl) = VISIBILITY_HIDDEN;
@@ -9267,7 +9288,7 @@ sparc_expand_compare_and_swap_12 (rtx result, rtx mem,
 bool
 sparc_frame_pointer_required (void)
 {
-  return !(leaf_function_p () && only_leaf_regs_used ());
+  return !(current_function_is_leaf && only_leaf_regs_used ());
 }
 
 /* The way this is structured, we can't eliminate SFP in favor of SP
