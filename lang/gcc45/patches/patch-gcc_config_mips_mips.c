$NetBSD$

--- gcc/config/mips/mips.c.orig	Sun Nov 21 10:38:43 2010
+++ gcc/config/mips/mips.c
@@ -1162,7 +1162,7 @@ static const struct mips_rtx_cost_data mips_rtx_cost_d
   }
 };
 
-static rtx mips_find_pic_call_symbol (rtx, rtx);
+static rtx mips_find_pic_call_symbol (rtx, rtx, bool);
 
 /* This hash table keeps track of implicit "mips16" and "nomips16" attributes
    for -mflip_mips16.  It maps decl names onto a boolean mode setting.  */
@@ -9007,6 +9007,11 @@ mips_interrupt_extra_call_saved_reg_p (unsigned int re
 static bool
 mips_cfun_call_saved_reg_p (unsigned int regno)
 {
+  /* If the user makes an ordinarily-call-saved register global,
+     that register is no longer call-saved.  */
+  if (global_regs[regno])
+    return false;
+
   /* Interrupt handlers need to save extra registers.  */
   if (cfun->machine->interrupt_handler_p
       && mips_interrupt_extra_call_saved_reg_p (regno))
@@ -14040,12 +14045,16 @@ mips_call_expr_from_insn (rtx insn, rtx *second_call)
 }
 
 /* REG is set in DEF.  See if the definition is one of the ways we load a
-   register with a symbol address for a mips_use_pic_fn_addr_reg_p call.  If
-   it is return the symbol reference of the function, otherwise return
-   NULL_RTX.  */
+   register with a symbol address for a mips_use_pic_fn_addr_reg_p call.
+   If it is, return the symbol reference of the function, otherwise return
+   NULL_RTX.
 
+   If RECURSE_P is true, use mips_find_pic_call_symbol to interpret
+   the values of source registers, otherwise treat such registers as
+   having an unknown value.  */
+
 static rtx
-mips_pic_call_symbol_from_set (df_ref def, rtx reg)
+mips_pic_call_symbol_from_set (df_ref def, rtx reg, bool recurse_p)
 {
   rtx def_insn, set;
 
@@ -14072,21 +14081,39 @@ mips_pic_call_symbol_from_set (df_ref def, rtx reg)
 	  return symbol;
 	}
 
-      /* Follow simple register copies.  */
-      if (REG_P (src))
-	return mips_find_pic_call_symbol (def_insn, src);
+      /* Follow at most one simple register copy.  Such copies are
+	 interesting in cases like:
+
+	     for (...)
+	       {
+	         locally_binding_fn (...);
+	       }
+
+	 and:
+
+	     locally_binding_fn (...);
+	     ...
+	     locally_binding_fn (...);
+
+	 where the load of locally_binding_fn can legitimately be
+	 hoisted or shared.  However, we do not expect to see complex
+	 chains of copies, so a full worklist solution to the problem
+	 would probably be overkill.  */
+      if (recurse_p && REG_P (src))
+	return mips_find_pic_call_symbol (def_insn, src, false);
     }
 
   return NULL_RTX;
 }
 
-/* Find the definition of the use of REG in INSN.  See if the definition is
-   one of the ways we load a register with a symbol address for a
-   mips_use_pic_fn_addr_reg_p call.  If it is return the symbol reference of
-   the function, otherwise return NULL_RTX.  */
+/* Find the definition of the use of REG in INSN.  See if the definition
+   is one of the ways we load a register with a symbol address for a
+   mips_use_pic_fn_addr_reg_p call.  If it is return the symbol reference
+   of the function, otherwise return NULL_RTX.  RECURSE_P is as for
+   mips_pic_call_symbol_from_set.  */
 
 static rtx
-mips_find_pic_call_symbol (rtx insn, rtx reg)
+mips_find_pic_call_symbol (rtx insn, rtx reg, bool recurse_p)
 {
   df_ref use;
   struct df_link *defs;
@@ -14098,7 +14125,7 @@ mips_find_pic_call_symbol (rtx insn, rtx reg)
   defs = DF_REF_CHAIN (use);
   if (!defs)
     return NULL_RTX;
-  symbol = mips_pic_call_symbol_from_set (defs->ref, reg);
+  symbol = mips_pic_call_symbol_from_set (defs->ref, reg, recurse_p);
   if (!symbol)
     return NULL_RTX;
 
@@ -14107,7 +14134,7 @@ mips_find_pic_call_symbol (rtx insn, rtx reg)
     {
       rtx other;
 
-      other = mips_pic_call_symbol_from_set (defs->ref, reg);
+      other = mips_pic_call_symbol_from_set (defs->ref, reg, recurse_p);
       if (!rtx_equal_p (symbol, other))
 	return NULL_RTX;
     }
@@ -14178,7 +14205,7 @@ mips_annotate_pic_calls (void)
       if (!REG_P (reg))
 	continue;
 
-      symbol = mips_find_pic_call_symbol (insn, reg);
+      symbol = mips_find_pic_call_symbol (insn, reg, true);
       if (symbol)
 	{
 	  mips_annotate_pic_call_expr (call, symbol);
