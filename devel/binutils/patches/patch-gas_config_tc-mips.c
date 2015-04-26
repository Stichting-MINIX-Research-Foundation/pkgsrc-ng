$NetBSD$

--- gas/config/tc-mips.c.orig	Tue Sep  4 14:21:03 2012
+++ gas/config/tc-mips.c
@@ -909,6 +909,9 @@ enum fix_vr4120_class
   NUM_FIX_VR4120_CLASSES
 };
 
+/* ...likewise -mtrap-zero-jump.  */
+static bfd_boolean mips_trap_zero_jump;
+
 /* ...likewise -mfix-loongson2f-jump.  */
 static bfd_boolean mips_fix_loongson2f_jump;
 
@@ -941,6 +944,8 @@ static bfd_boolean mips_fix_cn63xxp1;
    efficient expansion.  */
 
 static int mips_relax_branch;
+
+static int mips_fix_loongson2f_btb;
 
 /* The expansion of many macros depends on the type of symbol that
    they refer to.  For example, when generating position-dependent code,
@@ -1316,6 +1321,7 @@ static void macro_build (expressionS *, const char *, 
 static void mips16_macro_build
   (expressionS *, const char *, const char *, va_list *);
 static void load_register (int, expressionS *, int);
+static void macro_build (expressionS *, const char *, const char *, ...);
 static void macro_start (void);
 static void macro_end (void);
 static void macro (struct mips_cl_insn * ip);
@@ -3626,6 +3632,35 @@ nops_for_insn_or_target (int ignore, const struct mips
   return nops;
 }
 
+static void
+trap_zero_jump (struct mips_cl_insn * ip)
+{
+  if (strcmp (ip->insn_mo->name, "j") == 0
+      || strcmp (ip->insn_mo->name, "jr") == 0
+      || strcmp (ip->insn_mo->name, "jalr") == 0)
+    {
+      int sreg;
+
+      if (mips_opts.warn_about_macros)
+        return;
+
+      sreg = EXTRACT_OPERAND (0, RS, *ip);
+      if (mips_opts.isa == ISA_MIPS32
+          || mips_opts.isa == ISA_MIPS32R2
+          || mips_opts.isa == ISA_MIPS64
+          || mips_opts.isa == ISA_MIPS64R2)  
+	{
+	  expressionS ep;
+	  ep.X_op = O_constant;
+	  ep.X_add_number = 4096;
+	  macro_build (&ep, "tltiu", "s,j", sreg, BFD_RELOC_LO16);
+	}
+      else if (mips_opts.isa != ISA_UNKNOWN
+	       && mips_opts.isa != ISA_MIPS1)
+	macro_build (NULL, "teq", "s,t", sreg, 0);
+  }
+}
+
 /* Fix NOP issue: Replace nops by "or at,at,zero".  */
 
 static void
@@ -3663,6 +3698,16 @@ fix_loongson2f_jump (struct mips_cl_insn * ip)
       ep.X_add_number = 0xffff;
       macro_build (&ep, "ori", "t,r,i", ATREG, ATREG, BFD_RELOC_LO16);
       macro_build (NULL, "and", "d,v,t", sreg, sreg, ATREG);
+      /* Hide these three instructions to avoid getting a ``macro expanded into
+         multiple instructions'' warning. */
+      if (mips_relax.sequence != 2) {
+        mips_macro_warning.sizes[0] -= 3 * 4;
+        mips_macro_warning.insns[0] -= 3;
+      }
+      if (mips_relax.sequence != 1) {
+        mips_macro_warning.sizes[1] -= 3 * 4;
+        mips_macro_warning.insns[1] -= 3;
+      }
     }
 }
 
@@ -3718,6 +3763,11 @@ can_swap_branch_p (struct mips_cl_insn *ip)
   if (mips_opts.mips16 && history[0].fixp[0])
     return FALSE;
 
+  if (mips_fix_loongson2f)
+    fix_loongson2f (ip);
+  if (mips_trap_zero_jump)
+    trap_zero_jump (ip);
+
   /* If the branch is itself the target of a branch, we can not swap.
      We cheat on this; all we check for is whether there is a label on
      this instruction.  If there are any branches to anything other than
@@ -4764,6 +4814,45 @@ macro_read_relocs (va_list *args, bfd_reloc_code_real_
       r[i] = (bfd_reloc_code_real_type) va_arg (*args, int);
 }
 
+/* Fix jump through register issue on loongson2f processor for kernel code:
+   force a BTB clear before the jump to prevent it from being incorrectly
+   prefetched by the branch prediction engine. */
+
+static void
+macro_build_jrpatch (expressionS *ep, unsigned int sreg)
+{
+  if (!mips_fix_loongson2f_btb)
+    return;
+
+  if (sreg == ZERO || sreg == KT0 || sreg == KT1 || sreg == AT)
+    return;
+
+  if (!mips_opts.at)
+    {
+      as_warn (_("unable to apply loongson2f BTB workaround when .set noat"));
+      return;
+    }
+
+  /* li $at, COP_0_BTB_CLEAR | COP_0_RAS_DISABLE */
+  ep->X_op = O_constant;
+  ep->X_add_number = 3;
+  macro_build (ep, "ori", "t,r,i", AT, ZERO, BFD_RELOC_LO16);
+
+  /* dmtc0 $at, COP_0_DIAG */
+  macro_build (NULL, "dmtc0", "t,G", AT, 22);
+
+  /* Hide these two instructions to avoid getting a ``macro expanded into
+     multiple instructions'' warning. */
+  if (mips_relax.sequence != 2) {
+    mips_macro_warning.sizes[0] -= 2 * 4;
+    mips_macro_warning.insns[0] -= 2;
+  }
+  if (mips_relax.sequence != 1) {
+    mips_macro_warning.sizes[1] -= 2 * 4;
+    mips_macro_warning.insns[0] -= 2;
+  }
+}
+
 /* Build an instruction created by a macro expansion.  This is passed
    a pointer to the count of instructions created so far, an
    expression, the name of the instruction to build, an operand format
@@ -7637,6 +7726,26 @@ macro (struct mips_cl_insn *ip)
 	macro_build (NULL, ADDRESS_ADD_INSN, "d,v,t", treg, tempreg, breg);
       break;
 
+    case M_JR_S:
+      macro_build_jrpatch (&expr1, sreg);
+      macro_build (NULL, "jr", "s", sreg);
+      return;	/* didn't modify $at */
+
+    case M_J_S:
+      macro_build_jrpatch (&expr1, sreg);
+      macro_build (NULL, "j", "s", sreg);
+      return;	/* didn't modify $at */
+
+    case M_JALR_S:
+      macro_build_jrpatch (&expr1, sreg);
+      macro_build (NULL, "jalr", "s", sreg);
+      return;	/* didn't modify $at */
+
+    case M_JALR_DS:
+      macro_build_jrpatch (&expr1, sreg);
+      macro_build (NULL, "jalr", "d,s", dreg, sreg);
+      return;	/* didn't modify $at */
+
     case M_MSGSND:
       gas_assert (!mips_opts.micromips);
       {
@@ -14350,6 +14459,8 @@ enum options
     OPTION_SINGLE_FLOAT,
     OPTION_DOUBLE_FLOAT,
     OPTION_32,
+    OPTION_TRAP_ZERO_JUMP,
+    OPTION_NO_TRAP_ZERO_JUMP,
 #ifdef OBJ_ELF
     OPTION_CALL_SHARED,
     OPTION_CALL_NONPIC,
@@ -14364,6 +14475,8 @@ enum options
     OPTION_NO_PDR,
     OPTION_MVXWORKS_PIC,
 #endif /* OBJ_ELF */
+    OPTION_FIX_LOONGSON2F_BTB,
+    OPTION_NO_FIX_LOONGSON2F_BTB,
     OPTION_END_OF_ENUM    
   };
   
@@ -14421,6 +14534,8 @@ struct option md_longopts[] =
   {"mno-fix-loongson2f-jump", no_argument, NULL, OPTION_NO_FIX_LOONGSON2F_JUMP},
   {"mfix-loongson2f-nop", no_argument, NULL, OPTION_FIX_LOONGSON2F_NOP},
   {"mno-fix-loongson2f-nop", no_argument, NULL, OPTION_NO_FIX_LOONGSON2F_NOP},
+  {"mfix-loongson2f-btb", no_argument, NULL, OPTION_FIX_LOONGSON2F_BTB},
+  {"mno-fix-loongson2f-btb", no_argument, NULL, OPTION_NO_FIX_LOONGSON2F_BTB},
   {"mfix-vr4120",    no_argument, NULL, OPTION_FIX_VR4120},
   {"mno-fix-vr4120", no_argument, NULL, OPTION_NO_FIX_VR4120},
   {"mfix-vr4130",    no_argument, NULL, OPTION_FIX_VR4130},
@@ -14459,6 +14574,9 @@ struct option md_longopts[] =
      make testing easier.  */
   {"32",          no_argument, NULL, OPTION_32},
   
+  {"mtrap-zero-jump", no_argument, NULL, OPTION_TRAP_ZERO_JUMP},
+  {"mno-trap-zero-jump", no_argument, NULL, OPTION_NO_TRAP_ZERO_JUMP},
+
   /* ELF-specific options.  */
 #ifdef OBJ_ELF
   {"KPIC",        no_argument, NULL, OPTION_CALL_SHARED},
@@ -14750,6 +14868,14 @@ md_parse_option (int c, char *arg)
       mips_fix_vr4130 = 0;
       break;
 
+    case OPTION_FIX_LOONGSON2F_BTB:
+      mips_fix_loongson2f_btb = 1;
+      break;
+
+    case OPTION_NO_FIX_LOONGSON2F_BTB:
+      mips_fix_loongson2f_btb = 0;
+      break;
+
     case OPTION_FIX_CN63XXP1:
       mips_fix_cn63xxp1 = TRUE;
       break;
@@ -14782,6 +14908,14 @@ md_parse_option (int c, char *arg)
       mips_opts.sym32 = FALSE;
       break;
 
+    case OPTION_TRAP_ZERO_JUMP:
+      mips_trap_zero_jump = TRUE;
+      break;
+
+    case OPTION_NO_TRAP_ZERO_JUMP:
+      mips_trap_zero_jump = FALSE;
+      break;
+
 #ifdef OBJ_ELF
       /* When generating ELF code, we permit -KPIC and -call_shared to
 	 select SVR4_PIC, and -non_shared to select no PIC.  This is
@@ -19411,6 +19545,7 @@ MIPS options:\n\
   fprintf (stream, _("\
 -mfix-loongson2f-jump	work around Loongson2F JUMP instructions\n\
 -mfix-loongson2f-nop	work around Loongson2F NOP errata\n\
+-mfix-loongson2f-btb	work around Loongson2F BTB errata\n\
 -mfix-vr4120		work around certain VR4120 errata\n\
 -mfix-vr4130		work around VR4130 mflo/mfhi errata\n\
 -mfix-24k		insert a nop after ERET and DERET instructions\n\
