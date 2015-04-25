$NetBSD$

--- gcc/config/arm/thumb2.md.orig	Fri Apr  2 08:32:00 2010
+++ gcc/config/arm/thumb2.md
@@ -380,7 +380,7 @@
 	(not:SI (match_operator:SI 1 "arm_comparison_operator"
 		 [(match_operand 2 "cc_register" "") (const_int 0)])))]
   "TARGET_THUMB2"
-  "ite\\t%D1\;mov%D1\\t%0, #0\;mvn%d1\\t%0, #1"
+  "ite\\t%D1\;mvn%D1\\t%0, #0\;mvn%d1\\t%0, #1"
   [(set_attr "conds" "use")
    (set_attr "length" "10")]
 )
@@ -1108,6 +1108,7 @@
 	  (match_operand:SI 2 "low_reg_or_int_operand" "")]))]
   "TARGET_THUMB2
    && peep2_regno_dead_p(0, CC_REGNUM)
+   && (CONST_INT_P (operands[2]) || operands[1] == operands[0])
    && ((GET_CODE(operands[3]) != ROTATE && GET_CODE(operands[3]) != ROTATERT)
        || REG_P(operands[2]))"
   [(parallel
@@ -1120,10 +1121,10 @@
 )
 
 (define_insn "*thumb2_shiftsi3_short"
-  [(set (match_operand:SI   0 "low_register_operand" "=l")
+  [(set (match_operand:SI   0 "low_register_operand" "=l,l")
 	(match_operator:SI  3 "shift_operator"
-	 [(match_operand:SI 1 "low_register_operand"  "l")
-	  (match_operand:SI 2 "low_reg_or_int_operand" "lM")]))
+	 [(match_operand:SI 1 "low_register_operand"  "0,l")
+	  (match_operand:SI 2 "low_reg_or_int_operand" "l,M")]))
    (clobber (reg:CC CC_REGNUM))]
   "TARGET_THUMB2 && reload_completed
    && ((GET_CODE(operands[3]) != ROTATE && GET_CODE(operands[3]) != ROTATERT)
@@ -1207,7 +1208,7 @@
   [(set (match_operand:SI	  0 "s_register_operand" "=r")
 	(div:SI (match_operand:SI 1 "s_register_operand"  "r")
 		(match_operand:SI 2 "s_register_operand"  "r")))]
-  "TARGET_THUMB2 && arm_arch_hwdiv"
+  "(TARGET_THUMB2 || TARGET_ARM) && arm_arch_hwdiv"
   "sdiv%?\t%0, %1, %2"
   [(set_attr "predicable" "yes")
    (set_attr "insn" "sdiv")]
@@ -1217,7 +1218,7 @@
   [(set (match_operand:SI	   0 "s_register_operand" "=r")
 	(udiv:SI (match_operand:SI 1 "s_register_operand"  "r")
 		 (match_operand:SI 2 "s_register_operand"  "r")))]
-  "TARGET_THUMB2 && arm_arch_hwdiv"
+  "(TARGET_THUMB2 || TARGET_ARM) && arm_arch_hwdiv"
   "udiv%?\t%0, %1, %2"
   [(set_attr "predicable" "yes")
    (set_attr "insn" "udiv")]
