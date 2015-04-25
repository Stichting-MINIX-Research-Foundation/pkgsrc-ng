$NetBSD$

--- gcc/tree-vect-data-refs.c.orig	Fri Apr  2 19:54:46 2010
+++ gcc/tree-vect-data-refs.c
@@ -1450,7 +1450,7 @@ vect_analyze_group_access (struct data_reference *dr)
   loop_vec_info loop_vinfo = STMT_VINFO_LOOP_VINFO (stmt_info);
   bb_vec_info bb_vinfo = STMT_VINFO_BB_VINFO (stmt_info);
   HOST_WIDE_INT dr_step = TREE_INT_CST_LOW (step);
-  HOST_WIDE_INT stride;
+  HOST_WIDE_INT stride, last_accessed_element = 1;
   bool slp_impossible = false;
 
   /* For interleaving, STRIDE is STEP counted in elements, i.e., the size of the
@@ -1479,6 +1479,16 @@ vect_analyze_group_access (struct data_reference *dr)
 	      fprintf (vect_dump, " step ");
 	      print_generic_expr (vect_dump, step, TDF_SLIM);
 	    }
+
+	  if (loop_vinfo)
+	    {
+	      LOOP_VINFO_PEELING_FOR_GAPS (loop_vinfo) = true;
+
+	      if (vect_print_dump_info (REPORT_DETAILS))
+		fprintf (vect_dump, "Data access with gaps requires scalar "
+				    "epilogue loop");
+	    }
+
 	  return true;
 	}
       if (vect_print_dump_info (REPORT_DETAILS))
@@ -1531,6 +1541,7 @@ vect_analyze_group_access (struct data_reference *dr)
               next = DR_GROUP_NEXT_DR (vinfo_for_stmt (next));
               continue;
             }
+
           prev = next;
 
           /* Check that all the accesses have the same STEP.  */
@@ -1561,6 +1572,8 @@ vect_analyze_group_access (struct data_reference *dr)
               gaps += diff - 1;
 	    }
 
+	  last_accessed_element += diff;
+
           /* Store the gap from the previous member of the group. If there is no
              gap in the access, DR_GROUP_GAP is always 1.  */
           DR_GROUP_GAP (vinfo_for_stmt (next)) = diff;
@@ -1652,6 +1665,15 @@ vect_analyze_group_access (struct data_reference *dr)
             VEC_safe_push (gimple, heap, BB_VINFO_STRIDED_STORES (bb_vinfo),
                            stmt);
         }
+
+      /* There is a gap in the end of the group.  */
+      if (stride - last_accessed_element > 0 && loop_vinfo)
+	{
+	  LOOP_VINFO_PEELING_FOR_GAPS (loop_vinfo) = true;
+	  if (vect_print_dump_info (REPORT_DETAILS))
+	    fprintf (vect_dump, "Data access with gaps requires scalar "
+				"epilogue loop");
+	}
     }
 
   return true;
