$NetBSD$

--- gcc/config/arm/arm.c.orig	Mon Dec 27 12:45:02 2010
+++ gcc/config/arm/arm.c
@@ -3339,6 +3339,10 @@ arm_libcall_uses_aapcs_base (const_rtx libcall)
       add_libcall (libcall_htab,
 		   convert_optab_libfunc (trunc_optab, HFmode, SFmode));
       add_libcall (libcall_htab,
+		   convert_optab_libfunc (sfix_optab, SImode, DFmode));
+      add_libcall (libcall_htab,
+		   convert_optab_libfunc (ufix_optab, SImode, DFmode));
+      add_libcall (libcall_htab,
 		   convert_optab_libfunc (sfix_optab, DImode, DFmode));
       add_libcall (libcall_htab,
 		   convert_optab_libfunc (ufix_optab, DImode, DFmode));
@@ -3346,6 +3350,28 @@ arm_libcall_uses_aapcs_base (const_rtx libcall)
 		   convert_optab_libfunc (sfix_optab, DImode, SFmode));
       add_libcall (libcall_htab,
 		   convert_optab_libfunc (ufix_optab, DImode, SFmode));
+
+      /* Values from double-precision helper functions are returned in core
+	 registers if the selected core only supports single-precision
+	 arithmetic, even if we are using the hard-float ABI.  The same is
+	 true for single-precision helpers, but we will never be using the
+	 hard-float ABI on a CPU which doesn't support single-precision
+	 operations in hardware.  */
+      add_libcall (libcall_htab, optab_libfunc (add_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (sdiv_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (smul_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (neg_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (sub_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (eq_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (lt_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (le_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (ge_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (gt_optab, DFmode));
+      add_libcall (libcall_htab, optab_libfunc (unord_optab, DFmode));
+      add_libcall (libcall_htab, convert_optab_libfunc (sext_optab, DFmode,
+							SFmode));
+      add_libcall (libcall_htab, convert_optab_libfunc (trunc_optab, SFmode,
+							DFmode));
     }
 
   return libcall && htab_find (libcall_htab, libcall) != NULL;
@@ -18237,7 +18263,7 @@ neon_emit_pair_result_insn (enum machine_mode mode,
   rtx tmp1 = gen_reg_rtx (mode);
   rtx tmp2 = gen_reg_rtx (mode);
 
-  emit_insn (intfn (tmp1, op1, tmp2, op2));
+  emit_insn (intfn (tmp1, op1, op2, tmp2));
 
   emit_move_insn (mem, tmp1);
   mem = adjust_address (mem, mode, GET_MODE_SIZE (mode));
