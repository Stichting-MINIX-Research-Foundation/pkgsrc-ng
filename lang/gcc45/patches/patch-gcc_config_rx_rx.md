$NetBSD$

--- gcc/config/rx/rx.md.orig	Wed Apr 13 11:30:48 2011
+++ gcc/config/rx/rx.md
@@ -709,24 +709,24 @@
      (clobber (reg:CC CC_REG))])]
   ""
 {
-  /* ??? Support other conditions via cstore into a temporary?  */
-  if (GET_CODE (operands[1]) != EQ && GET_CODE (operands[1]) != NE)
+  /* One operand must be a constant or a register, the other must be a register.  */
+  if (   ! CONSTANT_P (operands[2])
+      && ! CONSTANT_P (operands[3])
+      && ! (REG_P (operands[2]) && REG_P (operands[3])))
     FAIL;
-  /* One operand must be a constant.  */
-  if (!CONSTANT_P (operands[2]) && !CONSTANT_P (operands[3]))
-    FAIL;
 })
 
 (define_insn_and_split "*movsicc"
-  [(set (match_operand:SI     0 "register_operand" "=r,r")
+  [(set (match_operand:SI     0 "register_operand" "=r,r,r")
 	(if_then_else:SI
-	  (match_operator 5 "rx_z_comparison_operator"
-	   [(match_operand:SI 3 "register_operand"  "r,r")
-	    (match_operand:SI 4 "rx_source_operand" "riQ,riQ")])
-	  (match_operand:SI   1 "nonmemory_operand" "i,ri")
-	  (match_operand:SI   2 "nonmemory_operand" "ri,i")))
+	  (match_operator     5 "comparison_operator"
+	   [(match_operand:SI 3 "register_operand"  "r,r,r")
+	    (match_operand:SI 4 "rx_source_operand" "riQ,riQ,riQ")])
+	  (match_operand:SI   1 "nonmemory_operand" "i,ri,r")
+	  (match_operand:SI   2 "nonmemory_operand" "ri,i,r")))
    (clobber (reg:CC CC_REG))]
-  "CONSTANT_P (operands[1]) || CONSTANT_P (operands[2])"
+  "(CONSTANT_P (operands[1]) || CONSTANT_P (operands[2]))
+    || (REG_P (operands[1]) && REG_P (operands[2]))"
   "#"
   "&& reload_completed"
   [(const_int 0)]
@@ -743,8 +743,11 @@
   op1 = operands[1];
   op2 = operands[2];
 
-  /* If OP2 is the constant, reverse the sense of the move.  */
-  if (!CONSTANT_P (operands[1]))
+  /* If OP2 is the constant, reverse the sense of the move.
+     Likewise if both operands are registers but OP1 == OP0.  */
+  if ((! CONSTANT_P (operands[1]) && CONSTANT_P (operands[2]))
+      || (REG_P (operands[1]) && REG_P (operands[2])
+          && rtx_equal_p (op0, op1)))
     {
       x = op1, op1 = op2, op2 = x;
       cmp_code = reverse_condition (cmp_code);
@@ -753,7 +756,7 @@
   /* If OP2 does not match the output, copy it into place.  We have allowed
      these alternatives so that the destination can legitimately be one of
      the comparison operands without increasing register pressure.  */
-  if (!rtx_equal_p (op0, op2))
+  if (! rtx_equal_p (op0, op2))
     emit_move_insn (op0, op2);
 
   x = gen_rtx_fmt_ee (cmp_code, VOIDmode, flags, const0_rtx);
@@ -769,14 +772,31 @@
 	    [(reg CC_REG) (const_int 0)])
 	  (match_operand:SI 1 "immediate_operand" "Sint08,Sint16,Sint24,i")
 	  (match_dup 0)))]
-  "reload_completed"
-{
-  if (GET_CODE (operands[2]) == EQ)
-    return "stz\t%1, %0";
-  else
-    return "stnz\t%1, %0";
-}
+  "reload_completed
+   && ((GET_CODE (operands[2]) == EQ) || (GET_CODE (operands[2]) == NE))"
+  {
+    if (GET_CODE (operands[2]) == EQ)
+      return "stz\t%1, %0";
+    else
+     return "stnz\t%1, %0";
+  }
   [(set_attr "length" "4,5,6,7")]
+)
+
+(define_insn "*stcc_reg"
+  [(set (match_operand:SI 0 "register_operand" "+r,r,r,r,r,r")
+	(if_then_else:SI
+	  (match_operator 2 "comparison_operator"
+	    [(reg CC_REG) (const_int 0)])
+	  (match_operand:SI 1 "nonmemory_operand"
+		              "r,Uint04,Sint08,Sint16,Sint24,i")
+	  (match_dup 0)))]
+  "reload_completed"
+  {
+    PUT_CODE (operands[2], reverse_condition (GET_CODE (operands[2])));
+    return "b%B2 1f\n\tmov %1, %0\n1:";
+  }
+  [(set_attr "length" "3,3,4,5,6,7")]
 )
 
 ;; Arithmetic Instructions
