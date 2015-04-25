$NetBSD$

--- gcc/config/i386/i386.md.orig	Fri Jan  7 13:02:29 2011
+++ gcc/config/i386/i386.md
@@ -2430,7 +2430,7 @@
   [(set_attr "type" "*,*,mmx,mmxmov,mmxmov,sselog1,ssemov,ssemov,ssemov,sselog1,ssemov,ssemov,ssemov")
    (set (attr "prefix")
      (if_then_else (eq_attr "alternative" "5,6,7,8")
-       (const_string "vex")
+       (const_string "maybe_vex")
        (const_string "orig")))
    (set_attr "mode" "DI,DI,DI,DI,DI,TI,DI,TI,DI,V4SF,V2SF,V4SF,V2SF")])
 
@@ -2468,21 +2468,15 @@
 	return "movdq2q\t{%1, %0|%0, %1}";
 
     case TYPE_SSEMOV:
-      if (TARGET_AVX)
-	{
-	  if (get_attr_mode (insn) == MODE_TI)
-	    return "vmovdqa\t{%1, %0|%0, %1}";
-	  else
-	    return "vmovq\t{%1, %0|%0, %1}";
-	}
-
       if (get_attr_mode (insn) == MODE_TI)
-	return "movdqa\t{%1, %0|%0, %1}";
-      /* FALLTHRU */
+	return "%vmovdqa\t{%1, %0|%0, %1}";
+      /* Handle broken assemblers that require movd instead of movq.  */
+      if (GENERAL_REG_P (operands[0]) || GENERAL_REG_P (operands[1]))
+	return "%vmovd\t{%1, %0|%0, %1}";
+      return "%vmovq\t{%1, %0|%0, %1}";
 
     case TYPE_MMXMOV:
-      /* Moves from and into integer register is done using movd
-	 opcode with REX prefix.  */
+      /* Handle broken assemblers that require movd instead of movq.  */
       if (GENERAL_REG_P (operands[0]) || GENERAL_REG_P (operands[1]))
 	return "movd\t{%1, %0|%0, %1}";
       return "movq\t{%1, %0|%0, %1}";
@@ -2878,7 +2872,7 @@
    && (reload_in_progress || reload_completed
        || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
        || (!TARGET_SSE_MATH && optimize_function_for_size_p (cfun)
-	   && standard_80387_constant_p (operands[1]))
+	   && standard_80387_constant_p (operands[1]) > 0)
        || GET_CODE (operands[1]) != CONST_DOUBLE
        || memory_operand (operands[0], SFmode))"
 {
@@ -2915,12 +2909,13 @@
 
     case 9: case 10: case 14: case 15:
       return "movd\t{%1, %0|%0, %1}";
-    case 12: case 13:
-      return "%vmovd\t{%1, %0|%0, %1}";
 
     case 11:
       return "movq\t{%1, %0|%0, %1}";
 
+    case 12: case 13:
+      return "%vmovd\t{%1, %0|%0, %1}";
+
     default:
       gcc_unreachable ();
     }
@@ -3048,11 +3043,10 @@
        || (!(TARGET_SSE2 && TARGET_SSE_MATH)
            && optimize_function_for_size_p (cfun)
            && !memory_operand (operands[0], DFmode)
-	   && standard_80387_constant_p (operands[1]))
+	   && standard_80387_constant_p (operands[1]) > 0)
        || GET_CODE (operands[1]) != CONST_DOUBLE
        || ((optimize_function_for_size_p (cfun)
-            || !TARGET_MEMORY_MISMATCH_STALL
-	    || reload_in_progress || reload_completed)
+            || !TARGET_MEMORY_MISMATCH_STALL)
  	   && memory_operand (operands[0], DFmode)))"
 {
   switch (which_alternative)
@@ -3067,6 +3061,7 @@
     case 3:
     case 4:
       return "#";
+
     case 5:
       switch (get_attr_mode (insn))
 	{
@@ -3200,7 +3195,7 @@
        || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
        || (!(TARGET_SSE2 && TARGET_SSE_MATH)
            && optimize_function_for_size_p (cfun)
-	   && standard_80387_constant_p (operands[1]))
+	   && standard_80387_constant_p (operands[1]) > 0)
        || GET_CODE (operands[1]) != CONST_DOUBLE
        || memory_operand (operands[0], DFmode))"
 {
@@ -3262,7 +3257,8 @@
 
     case 9:
     case 10:
-    return "%vmovd\t{%1, %0|%0, %1}";
+      /* Handle broken assemblers that require movd instead of movq.  */
+      return "%vmovd\t{%1, %0|%0, %1}";
 
     default:
       gcc_unreachable();
@@ -3340,7 +3336,7 @@
        || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
        || (!(TARGET_SSE2 && TARGET_SSE_MATH)
            && optimize_function_for_size_p (cfun)
-	   && standard_80387_constant_p (operands[1]))
+	   && standard_80387_constant_p (operands[1]) > 0)
        || GET_CODE (operands[1]) != CONST_DOUBLE
        || memory_operand (operands[0], DFmode))"
 {
@@ -3361,11 +3357,11 @@
       switch (get_attr_mode (insn))
 	{
 	case MODE_V4SF:
-	  return "xorps\t%0, %0";
+	  return "%vxorps\t%0, %d0";
 	case MODE_V2DF:
-	  return "xorpd\t%0, %0";
+	  return "%vxorpd\t%0, %d0";
 	case MODE_TI:
-	  return "pxor\t%0, %0";
+	  return "%vpxor\t%0, %d0";
 	default:
 	  gcc_unreachable ();
 	}
@@ -3375,28 +3371,56 @@
       switch (get_attr_mode (insn))
 	{
 	case MODE_V4SF:
-	  return "movaps\t{%1, %0|%0, %1}";
+	  return "%vmovaps\t{%1, %0|%0, %1}";
 	case MODE_V2DF:
-	  return "movapd\t{%1, %0|%0, %1}";
+	  return "%vmovapd\t{%1, %0|%0, %1}";
 	case MODE_TI:
-	  return "movdqa\t{%1, %0|%0, %1}";
+	  return "%vmovdqa\t{%1, %0|%0, %1}";
 	case MODE_DI:
-	  return "movq\t{%1, %0|%0, %1}";
+	  return "%vmovq\t{%1, %0|%0, %1}";
 	case MODE_DF:
-	  return "movsd\t{%1, %0|%0, %1}";
+	  if (TARGET_AVX)
+	    {
+	      if (REG_P (operands[0]) && REG_P (operands[1]))
+		return "vmovsd\t{%1, %0, %0|%0, %0, %1}";
+	      else
+		return "vmovsd\t{%1, %0|%0, %1}";
+	    }
+	  else
+	    return "movsd\t{%1, %0|%0, %1}";
 	case MODE_V1DF:
-	  return "movlpd\t{%1, %0|%0, %1}";
+	  if (TARGET_AVX)
+	    {
+	      if (REG_P (operands[0]))
+		return "vmovlpd\t{%1, %0, %0|%0, %0, %1}";
+	      else
+		return "vmovlpd\t{%1, %0|%0, %1}";
+	    }
+	  else
+	    return "movlpd\t{%1, %0|%0, %1}";
 	case MODE_V2SF:
-	  return "movlps\t{%1, %0|%0, %1}";
+	  if (TARGET_AVX)
+	    {
+	      if (REG_P (operands[0]))
+		return "vmovlps\t{%1, %0, %0|%0, %0, %1}";
+	      else
+		return "vmovlps\t{%1, %0|%0, %1}";
+	    }
+	  else
+	    return "movlps\t{%1, %0|%0, %1}";
 	default:
 	  gcc_unreachable ();
 	}
 
     default:
-      gcc_unreachable();
+      gcc_unreachable ();
     }
 }
   [(set_attr "type" "fmov,fmov,fmov,multi,multi,sselog1,ssemov,ssemov,ssemov")
+   (set (attr "prefix")
+     (if_then_else (eq_attr "alternative" "0,1,2,3,4")
+       (const_string "orig")
+       (const_string "maybe_vex")))
    (set (attr "prefix_data16")
      (if_then_else (eq_attr "mode" "V1DF")
        (const_string "1")
@@ -3543,7 +3567,8 @@
   "optimize_function_for_size_p (cfun)
    && !(MEM_P (operands[0]) && MEM_P (operands[1]))
    && (reload_in_progress || reload_completed
-       || standard_80387_constant_p (operands[1])
+       || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
+       || standard_80387_constant_p (operands[1]) > 0
        || GET_CODE (operands[1]) != CONST_DOUBLE
        || memory_operand (operands[0], XFmode))"
 {
@@ -3571,6 +3596,7 @@
   "optimize_function_for_speed_p (cfun)
    && !(MEM_P (operands[0]) && MEM_P (operands[1]))
    && (reload_in_progress || reload_completed
+       || (ix86_cmodel == CM_MEDIUM || ix86_cmodel == CM_LARGE)
        || GET_CODE (operands[1]) != CONST_DOUBLE
        || memory_operand (operands[0], XFmode))"
 {
@@ -3715,7 +3741,7 @@
     }
   else if (FP_REG_P (r))
     {
-      if (!standard_80387_constant_p (c))
+      if (standard_80387_constant_p (c) < 1)
 	FAIL;
     }
   else if (MMX_REG_P (r))
@@ -3747,7 +3773,7 @@
     }
   else if (FP_REG_P (r))
     {
-      if (!standard_80387_constant_p (c))
+      if (standard_80387_constant_p (c) < 1)
 	FAIL;
     }
   else if (MMX_REG_P (r))
@@ -17658,7 +17684,8 @@
    (set (match_operand:DI 1 "register_operand" "=S")
 	(plus:DI (match_dup 3)
 		 (const_int 8)))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "movsq"
   [(set_attr "type" "str")
    (set_attr "mode" "DI")
@@ -17673,7 +17700,8 @@
    (set (match_operand:SI 1 "register_operand" "=S")
 	(plus:SI (match_dup 3)
 		 (const_int 4)))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "movs{l|d}"
   [(set_attr "type" "str")
    (set_attr "mode" "SI")
@@ -17688,7 +17716,8 @@
    (set (match_operand:DI 1 "register_operand" "=S")
 	(plus:DI (match_dup 3)
 		 (const_int 4)))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "movs{l|d}"
   [(set_attr "type" "str")
    (set_attr "mode" "SI")
@@ -17703,7 +17732,8 @@
    (set (match_operand:SI 1 "register_operand" "=S")
 	(plus:SI (match_dup 3)
 		 (const_int 2)))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "movsw"
   [(set_attr "type" "str")
    (set_attr "memory" "both")
@@ -17718,7 +17748,8 @@
    (set (match_operand:DI 1 "register_operand" "=S")
 	(plus:DI (match_dup 3)
 		 (const_int 2)))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "movsw"
   [(set_attr "type" "str")
    (set_attr "memory" "both")
@@ -17733,7 +17764,8 @@
    (set (match_operand:SI 1 "register_operand" "=S")
 	(plus:SI (match_dup 3)
 		 (const_int 1)))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "movsb"
   [(set_attr "type" "str")
    (set_attr "memory" "both")
@@ -17748,7 +17780,8 @@
    (set (match_operand:DI 1 "register_operand" "=S")
 	(plus:DI (match_dup 3)
 		 (const_int 1)))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "movsb"
   [(set_attr "type" "str")
    (set_attr "memory" "both")
@@ -17779,7 +17812,8 @@
    (set (mem:BLK (match_dup 3))
 	(mem:BLK (match_dup 4)))
    (use (match_dup 5))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "rep{%;} movsq"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -17798,7 +17832,8 @@
    (set (mem:BLK (match_dup 3))
 	(mem:BLK (match_dup 4)))
    (use (match_dup 5))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "rep{%;} movs{l|d}"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -17817,7 +17852,8 @@
    (set (mem:BLK (match_dup 3))
 	(mem:BLK (match_dup 4)))
    (use (match_dup 5))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "rep{%;} movs{l|d}"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -17834,7 +17870,8 @@
    (set (mem:BLK (match_dup 3))
 	(mem:BLK (match_dup 4)))
    (use (match_dup 5))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "rep{%;} movsb"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -17851,7 +17888,8 @@
    (set (mem:BLK (match_dup 3))
 	(mem:BLK (match_dup 4)))
    (use (match_dup 5))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "rep{%;} movsb"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -17911,7 +17949,9 @@
   operands[3] = gen_rtx_PLUS (Pmode, operands[0],
 			      GEN_INT (GET_MODE_SIZE (GET_MODE
 						      (operands[2]))));
-  if (TARGET_SINGLE_STRINGOP || optimize_insn_for_size_p ())
+  /* Can't use this if the user has appropriated eax or edi.  */
+  if ((TARGET_SINGLE_STRINGOP || optimize_insn_for_size_p ())
+      && !(fixed_regs[AX_REG] || fixed_regs[DI_REG]))
     {
       emit_insn (gen_strset_singleop (operands[0], operands[1], operands[2],
 				      operands[3]));
@@ -17933,7 +17973,8 @@
    (set (match_operand:DI 0 "register_operand" "=D")
 	(plus:DI (match_dup 1)
 		 (const_int 8)))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[DI_REG])"
   "stosq"
   [(set_attr "type" "str")
    (set_attr "memory" "store")
@@ -17945,7 +17986,8 @@
    (set (match_operand:SI 0 "register_operand" "=D")
 	(plus:SI (match_dup 1)
 		 (const_int 4)))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[DI_REG])"
   "stos{l|d}"
   [(set_attr "type" "str")
    (set_attr "memory" "store")
@@ -17957,7 +17999,8 @@
    (set (match_operand:DI 0 "register_operand" "=D")
 	(plus:DI (match_dup 1)
 		 (const_int 4)))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[DI_REG])"
   "stos{l|d}"
   [(set_attr "type" "str")
    (set_attr "memory" "store")
@@ -17969,7 +18012,8 @@
    (set (match_operand:SI 0 "register_operand" "=D")
 	(plus:SI (match_dup 1)
 		 (const_int 2)))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[DI_REG])"
   "stosw"
   [(set_attr "type" "str")
    (set_attr "memory" "store")
@@ -17981,7 +18025,8 @@
    (set (match_operand:DI 0 "register_operand" "=D")
 	(plus:DI (match_dup 1)
 		 (const_int 2)))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[DI_REG])"
   "stosw"
   [(set_attr "type" "str")
    (set_attr "memory" "store")
@@ -17993,7 +18038,8 @@
    (set (match_operand:SI 0 "register_operand" "=D")
 	(plus:SI (match_dup 1)
 		 (const_int 1)))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[DI_REG])"
   "stosb"
   [(set_attr "type" "str")
    (set_attr "memory" "store")
@@ -18005,7 +18051,8 @@
    (set (match_operand:DI 0 "register_operand" "=D")
 	(plus:DI (match_dup 1)
 		 (const_int 1)))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[DI_REG])"
   "stosb"
   [(set_attr "type" "str")
    (set_attr "memory" "store")
@@ -18032,7 +18079,8 @@
 	(const_int 0))
    (use (match_operand:DI 2 "register_operand" "a"))
    (use (match_dup 4))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[CX_REG] || fixed_regs[DI_REG])"
   "rep{%;} stosq"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -18049,7 +18097,8 @@
 	(const_int 0))
    (use (match_operand:SI 2 "register_operand" "a"))
    (use (match_dup 4))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[CX_REG] || fixed_regs[DI_REG])"
   "rep{%;} stos{l|d}"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -18066,7 +18115,8 @@
 	(const_int 0))
    (use (match_operand:SI 2 "register_operand" "a"))
    (use (match_dup 4))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[CX_REG] || fixed_regs[DI_REG])"
   "rep{%;} stos{l|d}"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -18082,7 +18132,8 @@
 	(const_int 0))
    (use (match_operand:QI 2 "register_operand" "a"))
    (use (match_dup 4))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[CX_REG] || fixed_regs[DI_REG])"
   "rep{%;} stosb"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -18098,7 +18149,8 @@
 	(const_int 0))
    (use (match_operand:QI 2 "register_operand" "a"))
    (use (match_dup 4))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[CX_REG] || fixed_regs[DI_REG])"
   "rep{%;} stosb"
   [(set_attr "type" "str")
    (set_attr "prefix_rep" "1")
@@ -18119,8 +18171,8 @@
   if (optimize_insn_for_size_p () && !TARGET_INLINE_ALL_STRINGOPS)
     FAIL;
 
-  /* Can't use this if the user has appropriated esi or edi.  */
-  if (fixed_regs[SI_REG] || fixed_regs[DI_REG])
+  /* Can't use this if the user has appropriated ecx, esi or edi.  */
+  if (fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])
     FAIL;
 
   out = operands[0];
@@ -18214,7 +18266,8 @@
    (clobber (match_operand:SI 0 "register_operand" "=S"))
    (clobber (match_operand:SI 1 "register_operand" "=D"))
    (clobber (match_operand:SI 2 "register_operand" "=c"))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "repz{%;} cmpsb"
   [(set_attr "type" "str")
    (set_attr "mode" "QI")
@@ -18229,7 +18282,8 @@
    (clobber (match_operand:DI 0 "register_operand" "=S"))
    (clobber (match_operand:DI 1 "register_operand" "=D"))
    (clobber (match_operand:DI 2 "register_operand" "=c"))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "repz{%;} cmpsb"
   [(set_attr "type" "str")
    (set_attr "mode" "QI")
@@ -18265,7 +18319,8 @@
    (clobber (match_operand:SI 0 "register_operand" "=S"))
    (clobber (match_operand:SI 1 "register_operand" "=D"))
    (clobber (match_operand:SI 2 "register_operand" "=c"))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "repz{%;} cmpsb"
   [(set_attr "type" "str")
    (set_attr "mode" "QI")
@@ -18283,7 +18338,8 @@
    (clobber (match_operand:DI 0 "register_operand" "=S"))
    (clobber (match_operand:DI 1 "register_operand" "=D"))
    (clobber (match_operand:DI 2 "register_operand" "=c"))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[CX_REG] || fixed_regs[SI_REG] || fixed_regs[DI_REG])"
   "repz{%;} cmpsb"
   [(set_attr "type" "str")
    (set_attr "mode" "QI")
@@ -18295,7 +18351,7 @@
 	(unspec:SI [(match_operand:BLK 1 "general_operand" "")
 		    (match_operand:QI 2 "immediate_operand" "")
 		    (match_operand 3 "immediate_operand" "")] UNSPEC_SCAS))]
-  ""
+  "!TARGET_64BIT"
 {
  if (ix86_expand_strlen (operands[0], operands[1], operands[2], operands[3]))
    DONE;
@@ -18308,7 +18364,7 @@
 	(unspec:DI [(match_operand:BLK 1 "general_operand" "")
 		    (match_operand:QI 2 "immediate_operand" "")
 		    (match_operand 3 "immediate_operand" "")] UNSPEC_SCAS))]
-  ""
+  "TARGET_64BIT"
 {
  if (ix86_expand_strlen (operands[0], operands[1], operands[2], operands[3]))
    DONE;
@@ -18331,7 +18387,8 @@
 		    (match_operand:SI 4 "register_operand" "0")] UNSPEC_SCAS))
    (clobber (match_operand:SI 1 "register_operand" "=D"))
    (clobber (reg:CC FLAGS_REG))]
-  "!TARGET_64BIT"
+  "!TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[CX_REG] || fixed_regs[DI_REG])"
   "repnz{%;} scasb"
   [(set_attr "type" "str")
    (set_attr "mode" "QI")
@@ -18345,7 +18402,8 @@
 		    (match_operand:DI 4 "register_operand" "0")] UNSPEC_SCAS))
    (clobber (match_operand:DI 1 "register_operand" "=D"))
    (clobber (reg:CC FLAGS_REG))]
-  "TARGET_64BIT"
+  "TARGET_64BIT
+   && !(fixed_regs[AX_REG] || fixed_regs[CX_REG] || fixed_regs[DI_REG])"
   "repnz{%;} scasb"
   [(set_attr "type" "str")
    (set_attr "mode" "QI")
@@ -18499,7 +18557,8 @@
 (define_insn "*x86_mov<mode>cc_0_m1_neg"
   [(set (match_operand:SWI48 0 "register_operand" "=r")
 	(neg:SWI48 (match_operator 1 "ix86_carry_flag_operator"
-		    [(reg FLAGS_REG) (const_int 0)])))]
+		    [(reg FLAGS_REG) (const_int 0)])))
+   (clobber (reg:CC FLAGS_REG))]
   ""
   "sbb{<imodesuffix>}\t%0, %0"
   [(set_attr "type" "alu")
