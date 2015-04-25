$NetBSD$

--- gcc/config/rs6000/vector.md.orig	Fri Feb  4 16:31:48 2011
+++ gcc/config/rs6000/vector.md
@@ -441,27 +441,115 @@
   "VECTOR_UNIT_ALTIVEC_P (<MODE>mode)"
   "")
 
+(define_insn_and_split "*vector_uneq<mode>"
+  [(set (match_operand:VEC_F 0 "vfloat_operand" "")
+	(uneq:VEC_F (match_operand:VEC_F 1 "vfloat_operand" "")
+		    (match_operand:VEC_F 2 "vfloat_operand" "")))]
+  "VECTOR_UNIT_ALTIVEC_OR_VSX_P (<MODE>mode)"
+  "#"
+  ""
+  [(set (match_dup 3)
+	(gt:VEC_F (match_dup 1)
+		  (match_dup 2)))
+   (set (match_dup 4)
+	(gt:VEC_F (match_dup 2)
+		  (match_dup 1)))
+   (set (match_dup 0)
+	(not:VEC_F (ior:VEC_F (match_dup 3)
+			      (match_dup 4))))]
+  "
+{
+  operands[3] = gen_reg_rtx (<MODE>mode);
+  operands[4] = gen_reg_rtx (<MODE>mode);
+}")
+
+(define_insn_and_split "*vector_ltgt<mode>"
+  [(set (match_operand:VEC_F 0 "vfloat_operand" "")
+	(ltgt:VEC_F (match_operand:VEC_F 1 "vfloat_operand" "")
+		    (match_operand:VEC_F 2 "vfloat_operand" "")))]
+  "VECTOR_UNIT_ALTIVEC_OR_VSX_P (<MODE>mode)"
+  "#"
+  ""
+  [(set (match_dup 3)
+	(gt:VEC_F (match_dup 1)
+		  (match_dup 2)))
+   (set (match_dup 4)
+	(gt:VEC_F (match_dup 2)
+		  (match_dup 1)))
+   (set (match_dup 0)
+	(ior:VEC_F (match_dup 3)
+		   (match_dup 4)))]
+  "
+{
+  operands[3] = gen_reg_rtx (<MODE>mode);
+  operands[4] = gen_reg_rtx (<MODE>mode);
+}")
+
+(define_insn_and_split "*vector_ordered<mode>"
+  [(set (match_operand:VEC_F 0 "vfloat_operand" "")
+	(ordered:VEC_F (match_operand:VEC_F 1 "vfloat_operand" "")
+		       (match_operand:VEC_F 2 "vfloat_operand" "")))]
+  "VECTOR_UNIT_ALTIVEC_OR_VSX_P (<MODE>mode)"
+  "#"
+  ""
+  [(set (match_dup 3)
+	(ge:VEC_F (match_dup 1)
+		  (match_dup 2)))
+   (set (match_dup 4)
+	(ge:VEC_F (match_dup 2)
+		  (match_dup 1)))
+   (set (match_dup 0)
+	(ior:VEC_F (match_dup 3)
+		   (match_dup 4)))]
+  "
+{
+  operands[3] = gen_reg_rtx (<MODE>mode);
+  operands[4] = gen_reg_rtx (<MODE>mode);
+}")
+
+(define_insn_and_split "*vector_unordered<mode>"
+  [(set (match_operand:VEC_F 0 "vfloat_operand" "")
+	(unordered:VEC_F (match_operand:VEC_F 1 "vfloat_operand" "")
+			 (match_operand:VEC_F 2 "vfloat_operand" "")))]
+  "VECTOR_UNIT_ALTIVEC_OR_VSX_P (<MODE>mode)"
+  "#"
+  ""
+  [(set (match_dup 3)
+	(ge:VEC_F (match_dup 1)
+		  (match_dup 2)))
+   (set (match_dup 4)
+	(ge:VEC_F (match_dup 2)
+		  (match_dup 1)))
+   (set (match_dup 0)
+	(not:VEC_F (ior:VEC_F (match_dup 3)
+			      (match_dup 4))))]
+  "
+{
+  operands[3] = gen_reg_rtx (<MODE>mode);
+  operands[4] = gen_reg_rtx (<MODE>mode);
+}")
+
 ;; Note the arguments for __builtin_altivec_vsel are op2, op1, mask
 ;; which is in the reverse order that we want
 (define_expand "vector_select_<mode>"
   [(set (match_operand:VEC_L 0 "vlogical_operand" "")
 	(if_then_else:VEC_L
 	 (ne:CC (match_operand:VEC_L 3 "vlogical_operand" "")
-		(const_int 0))
+		(match_dup 4))
 	 (match_operand:VEC_L 2 "vlogical_operand" "")
 	 (match_operand:VEC_L 1 "vlogical_operand" "")))]
   "VECTOR_UNIT_ALTIVEC_OR_VSX_P (<MODE>mode)"
-  "")
+  "operands[4] = CONST0_RTX (<MODE>mode);")
 
 (define_expand "vector_select_<mode>_uns"
   [(set (match_operand:VEC_L 0 "vlogical_operand" "")
 	(if_then_else:VEC_L
 	 (ne:CCUNS (match_operand:VEC_L 3 "vlogical_operand" "")
-		   (const_int 0))
+		   (match_dup 4))
 	 (match_operand:VEC_L 2 "vlogical_operand" "")
 	 (match_operand:VEC_L 1 "vlogical_operand" "")))]
   "VECTOR_UNIT_ALTIVEC_OR_VSX_P (<MODE>mode)"
-  "")
+  "operands[4] = CONST0_RTX (<MODE>mode);")
 
 ;; Expansions that compare vectors producing a vector result and a predicate,
 ;; setting CR6 to indicate a combined status
