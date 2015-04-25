$NetBSD$

--- gcc/loop-doloop.c.orig	Mon Jul 19 09:58:53 2010
+++ gcc/loop-doloop.c
@@ -334,14 +334,11 @@ add_test (rtx cond, edge *e, basic_block dest)
    describes the loop, DESC describes the number of iterations of the
    loop, and DOLOOP_INSN is the low-overhead looping insn to emit at the
    end of the loop.  CONDITION is the condition separated from the
-   DOLOOP_SEQ.  COUNT is the number of iterations of the LOOP.
-   ZERO_EXTEND_P says to zero extend COUNT after the increment of it to
-   word_mode from FROM_MODE.  */
+   DOLOOP_SEQ.  COUNT is the number of iterations of the LOOP.  */
 
 static void
 doloop_modify (struct loop *loop, struct niter_desc *desc,
-	       rtx doloop_seq, rtx condition, rtx count,
-	       bool zero_extend_p, enum machine_mode from_mode)
+	       rtx doloop_seq, rtx condition, rtx count)
 {
   rtx counter_reg;
   rtx tmp, noloop = NULL_RTX;
@@ -415,12 +412,8 @@ doloop_modify (struct loop *loop, struct niter_desc *d
     }
 
   if (increment_count)
-    count = simplify_gen_binary (PLUS, from_mode, count, const1_rtx);
+    count = simplify_gen_binary (PLUS, mode, count, const1_rtx);
 
-  if (zero_extend_p)
-    count = simplify_gen_unary (ZERO_EXTEND, word_mode,
-				count, from_mode);
-
   /* Insert initialization of the count register into the loop header.  */
   start_sequence ();
   tmp = force_operand (count, counter_reg);
@@ -555,7 +548,6 @@ doloop_optimize (struct loop *loop)
   struct niter_desc *desc;
   unsigned word_mode_size;
   unsigned HOST_WIDE_INT word_mode_max;
-  bool zero_extend_p = false;
 
   if (dump_file)
     fprintf (dump_file, "Doloop: Processing loop %d.\n", loop->num);
@@ -630,7 +622,8 @@ doloop_optimize (struct loop *loop)
     {
       if (word_mode_size > GET_MODE_BITSIZE (mode))
 	{
-	  zero_extend_p = true;
+	  count = simplify_gen_unary (ZERO_EXTEND, word_mode,
+				      count, mode);
 	  iterations = simplify_gen_unary (ZERO_EXTEND, word_mode,
 					   iterations, mode);
 	  iterations_max = simplify_gen_unary (ZERO_EXTEND, word_mode,
@@ -674,8 +667,7 @@ doloop_optimize (struct loop *loop)
       return false;
     }
 
-  doloop_modify (loop, desc, doloop_seq, condition, count,
-		 zero_extend_p, mode);
+  doloop_modify (loop, desc, doloop_seq, condition, count);
   return true;
 }
 
