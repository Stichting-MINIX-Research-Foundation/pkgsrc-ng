$NetBSD$

--- gcc/config/i386/sse.md.orig	Sat Apr 16 07:53:39 2011
+++ gcc/config/i386/sse.md
@@ -354,18 +354,7 @@
   DONE;
 })
 
-(define_expand "avx_movup<avxmodesuffixf2c><avxmodesuffix>"
-  [(set (match_operand:AVXMODEF2P 0 "nonimmediate_operand" "")
-	(unspec:AVXMODEF2P
-	  [(match_operand:AVXMODEF2P 1 "nonimmediate_operand" "")]
-	  UNSPEC_MOVU))]
-  "AVX_VEC_FLOAT_MODE_P (<MODE>mode)"
-{
-  if (MEM_P (operands[0]) && MEM_P (operands[1]))
-    operands[1] = force_reg (<MODE>mode, operands[1]);
-})
-
-(define_insn "*avx_movup<avxmodesuffixf2c><avxmodesuffix>"
+(define_insn "avx_movup<avxmodesuffixf2c><avxmodesuffix>"
   [(set (match_operand:AVXMODEF2P 0 "nonimmediate_operand" "=x,m")
 	(unspec:AVXMODEF2P
 	  [(match_operand:AVXMODEF2P 1 "nonimmediate_operand" "xm,x")]
@@ -391,18 +380,7 @@
    (set_attr "prefix" "maybe_vex")
    (set_attr "mode" "TI")])
 
-(define_expand "<sse>_movup<ssemodesuffixf2c>"
-  [(set (match_operand:SSEMODEF2P 0 "nonimmediate_operand" "")
-	(unspec:SSEMODEF2P
-	  [(match_operand:SSEMODEF2P 1 "nonimmediate_operand" "")]
-	  UNSPEC_MOVU))]
-  "SSE_VEC_FLOAT_MODE_P (<MODE>mode)"
-{
-  if (MEM_P (operands[0]) && MEM_P (operands[1]))
-    operands[1] = force_reg (<MODE>mode, operands[1]);
-})
-
-(define_insn "*<sse>_movup<ssemodesuffixf2c>"
+(define_insn "<sse>_movup<ssemodesuffixf2c>"
   [(set (match_operand:SSEMODEF2P 0 "nonimmediate_operand" "=x,m")
 	(unspec:SSEMODEF2P
 	  [(match_operand:SSEMODEF2P 1 "nonimmediate_operand" "xm,x")]
@@ -414,18 +392,7 @@
    (set_attr "movu" "1")
    (set_attr "mode" "<MODE>")])
 
-(define_expand "avx_movdqu<avxmodesuffix>"
-  [(set (match_operand:AVXMODEQI 0 "nonimmediate_operand" "")
-	(unspec:AVXMODEQI
-	  [(match_operand:AVXMODEQI 1 "nonimmediate_operand" "")]
-	  UNSPEC_MOVU))]
-  "TARGET_AVX"
-{
-  if (MEM_P (operands[0]) && MEM_P (operands[1]))
-    operands[1] = force_reg (<MODE>mode, operands[1]);
-})
-
-(define_insn "*avx_movdqu<avxmodesuffix>"
+(define_insn "avx_movdqu<avxmodesuffix>"
   [(set (match_operand:AVXMODEQI 0 "nonimmediate_operand" "=x,m")
 	(unspec:AVXMODEQI
 	  [(match_operand:AVXMODEQI 1 "nonimmediate_operand" "xm,x")]
@@ -437,17 +404,7 @@
    (set_attr "prefix" "vex")
    (set_attr "mode" "<avxvecmode>")])
 
-(define_expand "sse2_movdqu"
-  [(set (match_operand:V16QI 0 "nonimmediate_operand" "")
-	(unspec:V16QI [(match_operand:V16QI 1 "nonimmediate_operand" "")]
-		      UNSPEC_MOVU))]
-  "TARGET_SSE2"
-{
-  if (MEM_P (operands[0]) && MEM_P (operands[1]))
-    operands[1] = force_reg (V16QImode, operands[1]);
-})
-
-(define_insn "*sse2_movdqu"
+(define_insn "sse2_movdqu"
   [(set (match_operand:V16QI 0 "nonimmediate_operand" "=x,m")
 	(unspec:V16QI [(match_operand:V16QI 1 "nonimmediate_operand" "xm,x")]
 		      UNSPEC_MOVU))]
@@ -1268,15 +1225,15 @@
 		(parallel [(const_int 0)]))
 	      (vec_select:DF (match_dup 1) (parallel [(const_int 1)])))
 	    (plusminus:DF
-	      (vec_select:DF (match_dup 1) (parallel [(const_int 2)]))
-	      (vec_select:DF (match_dup 1) (parallel [(const_int 3)]))))
-	  (vec_concat:V2DF
-	    (plusminus:DF
 	      (vec_select:DF
 		(match_operand:V4DF 2 "nonimmediate_operand" "xm")
 		(parallel [(const_int 0)]))
-	      (vec_select:DF (match_dup 2) (parallel [(const_int 1)])))
+	      (vec_select:DF (match_dup 2) (parallel [(const_int 1)]))))
+	  (vec_concat:V2DF
 	    (plusminus:DF
+	      (vec_select:DF (match_dup 1) (parallel [(const_int 2)]))
+	      (vec_select:DF (match_dup 1) (parallel [(const_int 3)])))
+	    (plusminus:DF
 	      (vec_select:DF (match_dup 2) (parallel [(const_int 2)]))
 	      (vec_select:DF (match_dup 2) (parallel [(const_int 3)]))))))]
   "TARGET_AVX"
@@ -3904,7 +3861,7 @@
   "TARGET_SSE"
 {
   if (!TARGET_AVX)
-    operands[1] = force_reg (V4SFmode, operands[1]);
+    operands[1] = force_reg (SFmode, operands[1]);
 })
 
 (define_insn "*vec_dupv4sf_avx"
@@ -4551,15 +4508,14 @@
   [(set (match_operand:V4DF 0 "register_operand"         "=x,x")
 	(vec_select:V4DF
 	  (vec_concat:V8DF
-	    (match_operand:V4DF 1 "nonimmediate_operand" "xm,x")
-	    (match_operand:V4DF 2 "nonimmediate_operand" " 1,xm"))
+	    (match_operand:V4DF 1 "nonimmediate_operand" " x,m")
+	    (match_operand:V4DF 2 "nonimmediate_operand" "xm,1"))
 	  (parallel [(const_int 0) (const_int 4)
 		     (const_int 2) (const_int 6)])))]
-  "TARGET_AVX
-   && (!MEM_P (operands[1]) || rtx_equal_p (operands[1], operands[2]))"
+  "TARGET_AVX"
   "@
-   vmovddup\t{%1, %0|%0, %1}
-   vunpcklpd\t{%2, %1, %0|%0, %1, %2}"
+   vunpcklpd\t{%2, %1, %0|%0, %1, %2}
+   vmovddup\t{%1, %0|%0, %1}"
   [(set_attr "type" "sselog")
    (set_attr "prefix" "vex")
    (set_attr "mode" "V4DF")])
@@ -4964,24 +4920,22 @@
 ;; Avoid combining registers from different units in a single alternative,
 ;; see comment above inline_secondary_memory_needed function in i386.c
 (define_insn "sse2_loadhpd"
-  [(set (match_operand:V2DF 0 "nonimmediate_operand"     "=x,x,x,o,o,o")
+  [(set (match_operand:V2DF 0 "nonimmediate_operand"     "=x,x,o,o,o")
 	(vec_concat:V2DF
 	  (vec_select:DF
-	    (match_operand:V2DF 1 "nonimmediate_operand" " 0,0,x,0,0,0")
+	    (match_operand:V2DF 1 "nonimmediate_operand" " 0,0,0,0,0")
 	    (parallel [(const_int 0)]))
-	  (match_operand:DF 2 "nonimmediate_operand"     " m,x,0,x,*f,r")))]
+	  (match_operand:DF 2 "nonimmediate_operand"     " m,x,x,*f,r")))]
   "TARGET_SSE2 && !(MEM_P (operands[1]) && MEM_P (operands[2]))"
   "@
    movhpd\t{%2, %0|%0, %2}
    unpcklpd\t{%2, %0|%0, %2}
-   shufpd\t{$1, %1, %0|%0, %1, 1}
    #
    #
    #"
-  [(set_attr "type" "ssemov,sselog,sselog,ssemov,fmov,imov")
-   (set_attr "prefix_data16" "1,*,*,*,*,*")
-   (set_attr "length_immediate" "*,*,1,*,*,*")
-   (set_attr "mode" "V1DF,V2DF,V2DF,DF,DF,DF")])
+  [(set_attr "type" "ssemov,sselog,ssemov,fmov,imov")
+   (set_attr "prefix_data16" "1,*,*,*,*")
+   (set_attr "mode" "V1DF,V2DF,DF,DF,DF")])
 
 (define_split
   [(set (match_operand:V2DF 0 "memory_operand" "")
@@ -5137,6 +5091,16 @@
    (set_attr "length_immediate" "*,*,*,1,*,*")
    (set_attr "mode" "DF,V1DF,V1DF,V2DF,V1DF,V1DF")])
 
+(define_expand "vec_dupv2df"
+  [(set (match_operand:V2DF 0 "register_operand" "")
+	(vec_duplicate:V2DF
+	  (match_operand:DF 1 "nonimmediate_operand" "")))]
+  "TARGET_SSE2"
+{
+  if (!TARGET_SSE3)
+    operands[1] = force_reg (DFmode, operands[1]);
+})
+
 (define_insn "*vec_dupv2df_sse3"
   [(set (match_operand:V2DF 0 "register_operand" "=x")
 	(vec_duplicate:V2DF
@@ -5147,7 +5111,7 @@
    (set_attr "prefix" "maybe_vex")
    (set_attr "mode" "DF")])
 
-(define_insn "vec_dupv2df"
+(define_insn "*vec_dupv2df"
   [(set (match_operand:V2DF 0 "register_operand" "=x")
 	(vec_duplicate:V2DF
 	  (match_operand:DF 1 "register_operand" "0")))]
@@ -7473,9 +7437,8 @@
   "@
    #
    #
-   %vmov{q}\t{%1, %0|%0, %1}"
+   mov{q}\t{%1, %0|%0, %1}"
   [(set_attr "type" "*,*,imov")
-   (set_attr "prefix" "*,*,maybe_vex")
    (set_attr "mode" "*,*,DI")])
 
 (define_insn "*sse2_storeq"
@@ -7513,11 +7476,11 @@
    vmovhps\t{%1, %0|%0, %1}
    vpsrldq\t{$8, %1, %0|%0, %1, 8}
    vmovq\t{%H1, %0|%0, %H1}
-   vmov{q}\t{%H1, %0|%0, %H1}"
+   mov{q}\t{%H1, %0|%0, %H1}"
   [(set_attr "type" "ssemov,sseishft1,ssemov,imov")
    (set_attr "length_immediate" "*,1,*,*")
    (set_attr "memory" "*,none,*,*")
-   (set_attr "prefix" "vex")
+   (set_attr "prefix" "vex,vex,vex,orig")
    (set_attr "mode" "V2SF,TI,TI,DI")])
 
 (define_insn "*vec_extractv2di_1_rex64"
@@ -7795,6 +7758,7 @@
        (const_string "vex")))
    (set_attr "mode" "TI,TI,TI,TI,TI,V2SF")])
 
+;; movd instead of movq is required to handle broken assemblers.
 (define_insn "*vec_concatv2di_rex64_sse4_1"
   [(set (match_operand:V2DI 0 "register_operand"     "=x ,x ,Yi,!x,x,x,x")
 	(vec_concat:V2DI
@@ -7804,7 +7768,7 @@
   "@
    pinsrq\t{$0x1, %2, %0|%0, %2, 0x1}
    movq\t{%1, %0|%0, %1}
-   movq\t{%1, %0|%0, %1}
+   movd\t{%1, %0|%0, %1}
    movq2dq\t{%1, %0|%0, %1}
    punpcklqdq\t{%2, %0|%0, %2}
    movlhps\t{%2, %0|%0, %2}
@@ -7815,6 +7779,7 @@
    (set_attr "length_immediate" "1,*,*,*,*,*,*")
    (set_attr "mode" "TI,TI,TI,TI,TI,V4SF,V2SF")])
 
+;; movd instead of movq is required to handle broken assemblers.
 (define_insn "*vec_concatv2di_rex64_sse"
   [(set (match_operand:V2DI 0 "register_operand"     "=Y2 ,Yi,!Y2,Y2,x,x")
 	(vec_concat:V2DI
@@ -7823,7 +7788,7 @@
   "TARGET_64BIT && TARGET_SSE"
   "@
    movq\t{%1, %0|%0, %1}
-   movq\t{%1, %0|%0, %1}
+   movd\t{%1, %0|%0, %1}
    movq2dq\t{%1, %0|%0, %1}
    punpcklqdq\t{%2, %0|%0, %2}
    movlhps\t{%2, %0|%0, %2}
@@ -10576,8 +10541,8 @@
   [(set (match_operand:SSEMODE 0 "register_operand" "=x,x")
 	(if_then_else:SSEMODE
 	  (match_operand:SSEMODE 3 "nonimmediate_operand" "x,m")
-	  (match_operand:SSEMODE 1 "vector_move_operand" "x,x")
-	  (match_operand:SSEMODE 2 "vector_move_operand" "xm,x")))]
+	  (match_operand:SSEMODE 1 "register_operand" "x,x")
+	  (match_operand:SSEMODE 2 "nonimmediate_operand" "xm,x")))]
   "TARGET_XOP"
   "vpcmov\t{%3, %2, %1, %0|%0, %1, %2, %3}"
   [(set_attr "type" "sse4arg")])
@@ -10586,8 +10551,8 @@
   [(set (match_operand:AVX256MODE 0 "register_operand" "=x,x")
 	(if_then_else:AVX256MODE
 	  (match_operand:AVX256MODE 3 "nonimmediate_operand" "x,m")
-	  (match_operand:AVX256MODE 1 "vector_move_operand" "x,x")
-	  (match_operand:AVX256MODE 2 "vector_move_operand" "xm,x")))]
+	  (match_operand:AVX256MODE 1 "register_operand" "x,x")
+	  (match_operand:AVX256MODE 2 "nonimmediate_operand" "xm,x")))]
   "TARGET_XOP"
   "vpcmov\t{%3, %2, %1, %0|%0, %1, %2, %3}"
   [(set_attr "type" "sse4arg")])
@@ -12136,8 +12101,7 @@
   [(set (match_operand:AVXMODEF2P 0 "register_operand" "=x")
 	(unspec:AVXMODEF2P
 	  [(match_operand:AVXMODEF2P 1 "memory_operand" "m")
-	   (match_operand:<avxpermvecmode> 2 "register_operand" "x")
-	   (match_dup 0)]
+	   (match_operand:<avxpermvecmode> 2 "register_operand" "x")]
 	  UNSPEC_MASKLOAD))]
   "TARGET_AVX"
   "vmaskmovp<avxmodesuffixf2c>\t{%1, %2, %0|%0, %2, %1}"
