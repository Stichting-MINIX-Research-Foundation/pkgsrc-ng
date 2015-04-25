$NetBSD$

--- gcc/config/sh/sh.md.orig	Sat Nov 21 22:51:07 2009
+++ gcc/config/sh/sh.md
@@ -149,6 +149,7 @@
   (UNSPEC_DIV_INV_TABLE	37)
   (UNSPEC_ASHIFTRT	35)
   (UNSPEC_THUNK		36)
+  (UNSPEC_CHKADD	38)
   (UNSPEC_SP_SET	40)
   (UNSPEC_SP_TEST	41)
   (UNSPEC_MOVUA		42)
@@ -8438,6 +8439,22 @@ label:
   i++;
 }")
 
+;; op0 = op1 + r12 but hide it before reload completed.  See the comment
+;; in symGOT_load expand.
+
+(define_insn_and_split "chk_guard_add"
+  [(set (match_operand:SI 0 "register_operand" "=&r")
+	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
+		    (reg:SI PIC_REG)]
+		   UNSPEC_CHKADD))]
+  "TARGET_SH1"
+  "#"
+  "TARGET_SH1 && reload_completed"
+  [(set (match_dup 0) (reg:SI PIC_REG))
+   (set (match_dup 0) (plus:SI (match_dup 0) (match_dup 1)))]
+  ""
+  [(set_attr "type" "arith")])
+
 (define_expand "sym_label2reg"
   [(set (match_operand:SI 0 "" "")
 	(const:SI (unspec:SI [(match_operand:SI 1 "" "")
@@ -8480,13 +8497,9 @@ label:
   else
     emit_move_insn (operands[2], operands[1]);
 
-  emit_move_insn (operands[3], gen_rtx_PLUS (Pmode,
-					     operands[2],
-					     gen_rtx_REG (Pmode, PIC_REG)));
-
   /* When stack protector inserts codes after the result is set to
-     R0, @(rX, r12) will cause a spill failure for R0.  Don't schedule
-     insns to avoid combining (set A (plus rX r12)) and (set op0 (mem A))
+     R0, @(rX, r12) will cause a spill failure for R0.  Use a unspec
+     insn to avoid combining (set A (plus rX r12)) and (set op0 (mem A))
      when rX is a GOT address for the guard symbol.  Ugly but doesn't
      matter because this is a rare situation.  */
   if (!TARGET_SHMEDIA
@@ -8496,7 +8509,10 @@ label:
       && GET_CODE (XVECEXP (XEXP (operands[1], 0), 0, 0)) == SYMBOL_REF
       && strcmp (XSTR (XVECEXP (XEXP (operands[1], 0), 0, 0), 0),
 		 \"__stack_chk_guard\") == 0)
-    emit_insn (gen_blockage ());
+    emit_insn (gen_chk_guard_add (operands[3], operands[2]));
+  else
+    emit_move_insn (operands[3], gen_rtx_PLUS (Pmode, operands[2],
+					       gen_rtx_REG (Pmode, PIC_REG)));
 
   /* N.B. This is not constant for a GOTPLT relocation.  */
   mem = gen_rtx_MEM (Pmode, operands[3]);
