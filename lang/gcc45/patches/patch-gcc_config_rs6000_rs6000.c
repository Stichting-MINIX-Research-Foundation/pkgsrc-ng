$NetBSD$

--- gcc/config/rs6000/rs6000.c.orig	Fri Feb  4 16:31:48 2011
+++ gcc/config/rs6000/rs6000.c
@@ -2511,7 +2511,7 @@ rs6000_override_options (const char *default_cpu)
   if (!rs6000_explicit_options.long_double)
     rs6000_long_double_type_size = RS6000_DEFAULT_LONG_DOUBLE_SIZE;
 
-#ifndef POWERPC_LINUX
+#if !defined(POWERPC_LINUX) && !defined(POWERPC_NETBSD)
   if (!rs6000_explicit_options.ieee)
     rs6000_ieeequad = 1;
 #endif
@@ -5426,10 +5426,11 @@ rs6000_legitimize_tls_address (rtx addr, enum tls_mode
 
       if (model == TLS_MODEL_GLOBAL_DYNAMIC)
 	{
-	  r3 = gen_rtx_REG (Pmode, 3);
 	  tga = rs6000_tls_get_addr ();
-	  emit_library_call_value (tga, dest, LCT_CONST, Pmode, 1, r3, Pmode);
+	  emit_library_call_value (tga, dest, LCT_CONST, Pmode,
+				   1, const0_rtx, Pmode);
 
+	  r3 = gen_rtx_REG (Pmode, 3);
 	  if (DEFAULT_ABI == ABI_AIX && TARGET_64BIT)
 	    insn = gen_tls_gd_aix64 (r3, got, addr, tga, const0_rtx);
 	  else if (DEFAULT_ABI == ABI_AIX && !TARGET_64BIT)
@@ -5446,11 +5447,12 @@ rs6000_legitimize_tls_address (rtx addr, enum tls_mode
 	}
       else if (model == TLS_MODEL_LOCAL_DYNAMIC)
 	{
-	  r3 = gen_rtx_REG (Pmode, 3);
 	  tga = rs6000_tls_get_addr ();
 	  tmp1 = gen_reg_rtx (Pmode);
-	  emit_library_call_value (tga, tmp1, LCT_CONST, Pmode, 1, r3, Pmode);
+	  emit_library_call_value (tga, tmp1, LCT_CONST, Pmode,
+				   1, const0_rtx, Pmode);
 
+	  r3 = gen_rtx_REG (Pmode, 3);
 	  if (DEFAULT_ABI == ABI_AIX && TARGET_64BIT)
 	    insn = gen_tls_ld_aix64 (r3, got, tga, const0_rtx);
 	  else if (DEFAULT_ABI == ABI_AIX && !TARGET_64BIT)
@@ -6694,7 +6696,7 @@ rs6000_emit_move (rtx dest, rtx source, enum machine_m
 
 /* Nonzero if we can use an AltiVec register to pass this arg.  */
 #define USE_ALTIVEC_FOR_ARG_P(CUM,MODE,TYPE,NAMED)		\
-  ((ALTIVEC_VECTOR_MODE (MODE) || VSX_VECTOR_MODE (MODE))	\
+  (ALTIVEC_OR_VSX_VECTOR_MODE (MODE)				\
    && (CUM)->vregno <= ALTIVEC_ARG_MAX_REG			\
    && TARGET_ALTIVEC_ABI					\
    && (NAMED))
@@ -6920,7 +6922,7 @@ function_arg_padding (enum machine_mode mode, const_tr
    existing library interfaces.
 
    Doubleword align SPE vectors.
-   Quadword align Altivec vectors.
+   Quadword align Altivec/VSX vectors.
    Quadword align large synthetic vector types.   */
 
 int
@@ -6937,7 +6939,7 @@ function_arg_boundary (enum machine_mode mode, tree ty
 	       && int_size_in_bytes (type) >= 8
 	       && int_size_in_bytes (type) < 16))
     return 64;
-  else if ((ALTIVEC_VECTOR_MODE (mode) || VSX_VECTOR_MODE (mode))
+  else if (ALTIVEC_OR_VSX_VECTOR_MODE (mode)
 	   || (type && TREE_CODE (type) == VECTOR_TYPE
 	       && int_size_in_bytes (type) >= 16))
     return 128;
@@ -7082,8 +7084,7 @@ function_arg_advance (CUMULATIVE_ARGS *cum, enum machi
     cum->nargs_prototype--;
 
   if (TARGET_ALTIVEC_ABI
-      && (ALTIVEC_VECTOR_MODE (mode)
-	  || VSX_VECTOR_MODE (mode)
+      && (ALTIVEC_OR_VSX_VECTOR_MODE (mode)
 	  || (type && TREE_CODE (type) == VECTOR_TYPE
 	      && int_size_in_bytes (type) == 16)))
     {
@@ -7677,8 +7678,7 @@ function_arg (CUMULATIVE_ARGS *cum, enum machine_mode 
     else
       return gen_rtx_REG (mode, cum->vregno);
   else if (TARGET_ALTIVEC_ABI
-	   && (ALTIVEC_VECTOR_MODE (mode)
-	       || VSX_VECTOR_MODE (mode)
+	   && (ALTIVEC_OR_VSX_VECTOR_MODE (mode)
 	       || (type && TREE_CODE (type) == VECTOR_TYPE
 		   && int_size_in_bytes (type) == 16)))
     {
@@ -15803,6 +15803,10 @@ rs6000_emit_vector_compare_inner (enum rtx_code code, 
     case EQ:
     case GT:
     case GTU:
+    case ORDERED:
+    case UNORDERED:
+    case UNEQ:
+    case LTGT:
       mask = gen_reg_rtx (mode);
       emit_insn (gen_rtx_SET (VOIDmode,
 			      mask,
@@ -16007,7 +16011,7 @@ rs6000_emit_vector_cond_expr (rtx dest, rtx op_true, r
       op_false = tmp;
     }
 
-  cond2 = gen_rtx_fmt_ee (NE, cc_mode, mask, const0_rtx);
+  cond2 = gen_rtx_fmt_ee (NE, cc_mode, mask, CONST0_RTX (dest_mode));
   emit_insn (gen_rtx_SET (VOIDmode,
 			  dest,
 			  gen_rtx_IF_THEN_ELSE (dest_mode,
@@ -18280,7 +18284,7 @@ emit_frame_save (rtx frame_reg, rtx frame_ptr, enum ma
 
   /* Some cases that need register indexed addressing.  */
   if ((TARGET_ALTIVEC_ABI && ALTIVEC_VECTOR_MODE (mode))
-      || (TARGET_VSX && VSX_VECTOR_MODE (mode))
+      || (TARGET_VSX && ALTIVEC_OR_VSX_VECTOR_MODE (mode))
       || (TARGET_E500_DOUBLE && mode == DFmode)
       || (TARGET_SPE_ABI
 	  && SPE_VECTOR_MODE (mode)
@@ -18427,7 +18431,7 @@ rs6000_savres_routine_name (rs6000_stack_t *info, int 
     }
   else if (DEFAULT_ABI == ABI_AIX)
     {
-#ifndef POWERPC_LINUX
+#if !defined(POWERPC_LINUX) && !defined(POWERPC_NETBSD)
       /* No out-of-line save/restore routines for GPRs on AIX.  */
       gcc_assert (!TARGET_AIX || !gpr);
 #endif
@@ -18437,7 +18441,7 @@ rs6000_savres_routine_name (rs6000_stack_t *info, int 
 	prefix = (savep
 		  ? (lr ? "_savegpr0_" : "_savegpr1_")
 		  : (lr ? "_restgpr0_" : "_restgpr1_"));
-#ifdef POWERPC_LINUX
+#if defined(POWERPC_LINUX) || defined(POWERPC_NETBSD)
       else if (lr)
 	prefix = (savep ? "_savefpr_" : "_restfpr_");
 #endif
@@ -18504,7 +18508,7 @@ rs6000_emit_stack_reset (rs6000_stack_t *info,
 {
   /* This blockage is needed so that sched doesn't decide to move
      the sp change before the register restores.  */
-  if (frame_reg_rtx != sp_reg_rtx
+  if (DEFAULT_ABI == ABI_V4
       || (TARGET_SPE_ABI
 	  && info->spe_64bit_regs_used != 0
 	  && info->first_gp_reg_save != 32))
@@ -18701,7 +18705,7 @@ rs6000_savres_strategy (rs6000_stack_t *info, bool sav
   strategy = (using_multiple_p
 	      | (savres_fprs_inline << 1)
 	      | (savres_gprs_inline << 2));
-#ifdef POWERPC_LINUX
+#if defined(POWERPC_LINUX) || defined(POWERPC_NETBSD)
   if (TARGET_64BIT)
     {
       if (!savres_fprs_inline)
@@ -25565,14 +25569,13 @@ rs6000_function_value (const_tree valtype,
   else if (TREE_CODE (valtype) == COMPLEX_TYPE
 	   && targetm.calls.split_complex_arg)
     return rs6000_complex_function_value (mode);
+  /* VSX is a superset of Altivec and adds V2DImode/V2DFmode.  Since the same
+     return register is used in both cases, and we won't see V2DImode/V2DFmode
+     for pure altivec, combine the two cases.  */
   else if (TREE_CODE (valtype) == VECTOR_TYPE
 	   && TARGET_ALTIVEC && TARGET_ALTIVEC_ABI
-	   && ALTIVEC_VECTOR_MODE (mode))
+	   && ALTIVEC_OR_VSX_VECTOR_MODE (mode))
     regno = ALTIVEC_ARG_RETURN;
-  else if (TREE_CODE (valtype) == VECTOR_TYPE
-	   && TARGET_VSX && TARGET_ALTIVEC_ABI
-	   && VSX_VECTOR_MODE (mode))
-    regno = ALTIVEC_ARG_RETURN;
   else if (TARGET_E500_DOUBLE && TARGET_HARD_FLOAT
 	   && (mode == DFmode || mode == DCmode
 	       || mode == TFmode || mode == TCmode))
@@ -25611,11 +25614,11 @@ rs6000_libcall_value (enum machine_mode mode)
 	   && TARGET_HARD_FLOAT && TARGET_FPRS
            && ((TARGET_SINGLE_FLOAT && mode == SFmode) || TARGET_DOUBLE_FLOAT))
     regno = FP_ARG_RETURN;
-  else if (ALTIVEC_VECTOR_MODE (mode)
+  /* VSX is a superset of Altivec and adds V2DImode/V2DFmode.  Since the same
+     return register is used in both cases, and we won't see V2DImode/V2DFmode
+     for pure altivec, combine the two cases.  */
+  else if (ALTIVEC_OR_VSX_VECTOR_MODE (mode)
 	   && TARGET_ALTIVEC && TARGET_ALTIVEC_ABI)
-    regno = ALTIVEC_ARG_RETURN;
-  else if (VSX_VECTOR_MODE (mode)
-	   && TARGET_VSX && TARGET_ALTIVEC_ABI)
     regno = ALTIVEC_ARG_RETURN;
   else if (COMPLEX_MODE_P (mode) && targetm.calls.split_complex_arg)
     return rs6000_complex_function_value (mode);
