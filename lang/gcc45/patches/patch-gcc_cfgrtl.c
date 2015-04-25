$NetBSD$

--- gcc/cfgrtl.c.orig	Mon Sep 20 21:30:35 2010
+++ gcc/cfgrtl.c
@@ -1116,6 +1116,7 @@ force_nonfallthru_and_redirect (edge e, basic_block ta
   rtx note;
   edge new_edge;
   int abnormal_edge_flags = 0;
+  bool asm_goto_edge = false;
   int loc;
 
   /* In the case the last instruction is conditional jump to the next
@@ -1195,8 +1196,28 @@ force_nonfallthru_and_redirect (edge e, basic_block ta
 	}
     }
 
-  if (EDGE_COUNT (e->src->succs) >= 2 || abnormal_edge_flags)
+  /* If e->src ends with asm goto, see if any of the ASM_OPERANDS_LABELs
+     don't point to target label.  */
+  if (JUMP_P (BB_END (e->src))
+      && target != EXIT_BLOCK_PTR
+      && e->dest == target
+      && (e->flags & EDGE_FALLTHRU)
+      && (note = extract_asm_operands (PATTERN (BB_END (e->src)))))
     {
+      int i, n = ASM_OPERANDS_LABEL_LENGTH (note);
+
+      for (i = 0; i < n; ++i)
+	if (XEXP (ASM_OPERANDS_LABEL (note, i), 0) == BB_HEAD (target))
+	  {
+	    asm_goto_edge = true;
+	    break;
+	  }
+    }
+
+  if (EDGE_COUNT (e->src->succs) >= 2 || abnormal_edge_flags || asm_goto_edge)
+    {
+      gcov_type count = e->count;
+      int probability = e->probability;
       /* Create the new structures.  */
 
       /* If the old block ended with a tablejump, skip its table
@@ -1207,7 +1228,7 @@ force_nonfallthru_and_redirect (edge e, basic_block ta
       note = NEXT_INSN (note);
 
       jump_block = create_basic_block (note, NULL, e->src);
-      jump_block->count = e->count;
+      jump_block->count = count;
       jump_block->frequency = EDGE_FREQUENCY (e);
       jump_block->loop_depth = target->loop_depth;
 
@@ -1223,13 +1244,27 @@ force_nonfallthru_and_redirect (edge e, basic_block ta
 
       /* Wire edge in.  */
       new_edge = make_edge (e->src, jump_block, EDGE_FALLTHRU);
-      new_edge->probability = e->probability;
-      new_edge->count = e->count;
+      new_edge->probability = probability;
+      new_edge->count = count;
 
       /* Redirect old edge.  */
       redirect_edge_pred (e, jump_block);
       e->probability = REG_BR_PROB_BASE;
 
+      /* If asm goto has any label refs to target's label,
+	 add also edge from asm goto bb to target.  */
+      if (asm_goto_edge)
+	{
+	  new_edge->probability /= 2;
+	  new_edge->count /= 2;
+	  jump_block->count /= 2;
+	  jump_block->frequency /= 2;
+	  new_edge = make_edge (new_edge->src, target,
+				e->flags & ~EDGE_FALLTHRU);
+	  new_edge->probability = probability - probability / 2;
+	  new_edge->count = count - count / 2;
+	}
+
       new_bb = jump_block;
     }
   else
@@ -1640,9 +1675,10 @@ rtl_dump_bb (basic_block bb, FILE *outf, int indent, i
       putc ('\n', outf);
     }
 
-  for (insn = BB_HEAD (bb), last = NEXT_INSN (BB_END (bb)); insn != last;
-       insn = NEXT_INSN (insn))
-    print_rtl_single (outf, insn);
+  if (bb->index != ENTRY_BLOCK && bb->index != EXIT_BLOCK)
+    for (insn = BB_HEAD (bb), last = NEXT_INSN (BB_END (bb)); insn != last;
+	 insn = NEXT_INSN (insn))
+      print_rtl_single (outf, insn);
 
   if (df)
     {
@@ -2754,6 +2790,11 @@ cfg_layout_merge_blocks (basic_block a, basic_block b)
       rtx first = BB_END (a), last;
 
       last = emit_insn_after_noloc (b->il.rtl->header, BB_END (a), a);
+      /* The above might add a BARRIER as BB_END, but as barriers
+	 aren't valid parts of a bb, remove_insn doesn't update
+	 BB_END if it is a barrier.  So adjust BB_END here.  */
+      while (BB_END (a) != first && BARRIER_P (BB_END (a)))
+	BB_END (a) = PREV_INSN (BB_END (a));
       delete_insn_chain (NEXT_INSN (first), last, false);
       b->il.rtl->header = NULL;
     }
