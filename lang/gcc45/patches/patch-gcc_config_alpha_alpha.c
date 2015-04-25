$NetBSD$

--- gcc/config/alpha/alpha.c.orig	Tue Aug  3 18:44:56 2010
+++ gcc/config/alpha/alpha.c
@@ -2464,7 +2464,7 @@ alpha_emit_conditional_branch (rtx operands[], enum ma
     {
     case EQ:  case LE:  case LT:  case LEU:  case LTU:
     case UNORDERED:
-      /* We have these compares: */
+      /* We have these compares.  */
       cmp_code = code, branch_code = NE;
       break;
 
@@ -2701,13 +2701,15 @@ alpha_emit_conditional_move (rtx cmp, enum machine_mod
       switch (code)
 	{
 	case EQ: case LE: case LT: case LEU: case LTU:
+	case UNORDERED:
 	  /* We have these compares.  */
 	  cmp_code = code, code = NE;
 	  break;
 
 	case NE:
-	  /* This must be reversed.  */
-	  cmp_code = EQ, code = EQ;
+	case ORDERED:
+	  /* These must be reversed.  */
+	  cmp_code = reverse_condition (code), code = EQ;
 	  break;
 
 	case GE: case GT: case GEU: case GTU:
@@ -2727,6 +2729,14 @@ alpha_emit_conditional_move (rtx cmp, enum machine_mod
 	  gcc_unreachable ();
 	}
 
+      if (cmp_mode == DImode)
+	{
+	  if (!reg_or_0_operand (op0, DImode))
+	    op0 = force_reg (DImode, op0);
+	  if (!reg_or_8bit_operand (op1, DImode))
+	    op1 = force_reg (DImode, op1);
+	}
+
       tem = gen_reg_rtx (cmp_mode);
       emit_insn (gen_rtx_SET (VOIDmode, tem,
 			      gen_rtx_fmt_ee (cmp_code, cmp_mode,
@@ -2738,6 +2748,14 @@ alpha_emit_conditional_move (rtx cmp, enum machine_mod
       local_fast_math = 1;
     }
 
+  if (cmp_mode == DImode)
+    {
+      if (!reg_or_0_operand (op0, DImode))
+	op0 = force_reg (DImode, op0);
+      if (!reg_or_8bit_operand (op1, DImode))
+	op1 = force_reg (DImode, op1);
+    }
+
   /* We may be able to use a conditional move directly.
      This avoids emitting spurious compares.  */
   if (signed_comparison_operator (cmp, VOIDmode)
@@ -2756,11 +2774,13 @@ alpha_emit_conditional_move (rtx cmp, enum machine_mod
   switch (code)
     {
     case EQ:  case LE:  case LT:  case LEU:  case LTU:
+    case UNORDERED:
       /* We have these compares: */
       break;
 
     case NE:
-      /* This must be reversed.  */
+    case ORDERED:
+      /* These must be reversed.  */
       code = reverse_condition (code);
       cmov_code = EQ;
       break;
@@ -4915,6 +4935,13 @@ alpha_gp_save_rtx (void)
   return m;
 }
 
+static void
+alpha_instantiate_decls (void)
+{
+  if (cfun->machine->gp_save_rtx != NULL_RTX)
+    instantiate_decl_rtl (cfun->machine->gp_save_rtx);
+}
+
 static int
 alpha_ra_ever_killed (void)
 {
@@ -11124,6 +11151,9 @@ alpha_init_libfuncs (void)
 #define TARGET_ARG_PARTIAL_BYTES alpha_arg_partial_bytes
 #undef TARGET_TRAMPOLINE_INIT
 #define TARGET_TRAMPOLINE_INIT alpha_trampoline_init
+
+#undef TARGET_INSTANTIATE_DECLS
+#define TARGET_INSTANTIATE_DECLS alpha_instantiate_decls
 
 #undef TARGET_SECONDARY_RELOAD
 #define TARGET_SECONDARY_RELOAD alpha_secondary_reload
