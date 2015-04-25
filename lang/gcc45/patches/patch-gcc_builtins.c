$NetBSD$

--- gcc/builtins.c.orig	Tue Dec  7 15:11:46 2010
+++ gcc/builtins.c
@@ -347,7 +347,7 @@ bool
 can_trust_pointer_alignment (void)
 {
   /* We rely on TER to compute accurate alignment information.  */
-  return (optimize && flag_tree_ter);
+  return (!STRICT_ALIGNMENT && optimize && flag_tree_ter);
 }
 
 /* Return the alignment in bits of EXP, a pointer valued expression.
@@ -3896,9 +3896,9 @@ expand_builtin_bzero (tree exp)
 }
 
 /* Expand expression EXP, which is a call to the memcmp built-in function.
-   Return NULL_RTX if we failed and the
-   caller should emit a normal call, otherwise try to get the result in
-   TARGET, if convenient (and in mode MODE, if that's convenient).  */
+   Return NULL_RTX if we failed and the caller should emit a normal call,
+   otherwise try to get the result in TARGET, if convenient (and in mode
+   MODE, if that's convenient).  */
 
 static rtx
 expand_builtin_memcmp (tree exp, ATTRIBUTE_UNUSED rtx target,
@@ -3910,7 +3910,10 @@ expand_builtin_memcmp (tree exp, ATTRIBUTE_UNUSED rtx 
  			 POINTER_TYPE, POINTER_TYPE, INTEGER_TYPE, VOID_TYPE))
     return NULL_RTX;
 
-#if defined HAVE_cmpmemsi || defined HAVE_cmpstrnsi
+  /* Note: The cmpstrnsi pattern, if it exists, is not suitable for
+     implementing memcmp because it will stop if it encounters two
+     zero bytes.  */
+#if defined HAVE_cmpmemsi
   {
     rtx arg1_rtx, arg2_rtx, arg3_rtx;
     rtx result;
@@ -3925,16 +3928,9 @@ expand_builtin_memcmp (tree exp, ATTRIBUTE_UNUSED rtx 
       = get_pointer_alignment (arg2, BIGGEST_ALIGNMENT) / BITS_PER_UNIT;
     enum machine_mode insn_mode;
 
-#ifdef HAVE_cmpmemsi
     if (HAVE_cmpmemsi)
       insn_mode = insn_data[(int) CODE_FOR_cmpmemsi].operand[0].mode;
     else
-#endif
-#ifdef HAVE_cmpstrnsi
-    if (HAVE_cmpstrnsi)
-      insn_mode = insn_data[(int) CODE_FOR_cmpstrnsi].operand[0].mode;
-    else
-#endif
       return NULL_RTX;
 
     /* If we don't have POINTER_TYPE, call the function.  */
@@ -3959,18 +3955,10 @@ expand_builtin_memcmp (tree exp, ATTRIBUTE_UNUSED rtx 
 	set_mem_size (arg2_rtx, arg3_rtx);
       }
 
-#ifdef HAVE_cmpmemsi
     if (HAVE_cmpmemsi)
       insn = gen_cmpmemsi (result, arg1_rtx, arg2_rtx, arg3_rtx,
 			   GEN_INT (MIN (arg1_align, arg2_align)));
     else
-#endif
-#ifdef HAVE_cmpstrnsi
-    if (HAVE_cmpstrnsi)
-      insn = gen_cmpstrnsi (result, arg1_rtx, arg2_rtx, arg3_rtx,
-			    GEN_INT (MIN (arg1_align, arg2_align)));
-    else
-#endif
       gcc_unreachable ();
 
     if (insn)
@@ -3996,7 +3984,7 @@ expand_builtin_memcmp (tree exp, ATTRIBUTE_UNUSED rtx 
     else
       return convert_to_mode (mode, result, 0);
   }
-#endif
+#endif /* HAVE_cmpmemsi.  */
 
   return NULL_RTX;
 }
