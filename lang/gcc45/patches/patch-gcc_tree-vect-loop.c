$NetBSD$

--- gcc/tree-vect-loop.c.orig	Tue Mar  1 17:04:26 2011
+++ gcc/tree-vect-loop.c
@@ -711,6 +711,7 @@ new_loop_vec_info (struct loop *loop)
   LOOP_VINFO_STRIDED_STORES (res) = VEC_alloc (gimple, heap, 10);
   LOOP_VINFO_SLP_INSTANCES (res) = VEC_alloc (slp_instance, heap, 10);
   LOOP_VINFO_SLP_UNROLLING_FACTOR (res) = 1;
+  LOOP_VINFO_PEELING_FOR_GAPS (res) = false;
 
   return res;
 }
@@ -2053,6 +2054,10 @@ vect_estimate_min_profitable_iters (loop_vec_info loop
 	  peel_iters_prologue = niters < peel_iters_prologue ?
 					niters : peel_iters_prologue;
 	  peel_iters_epilogue = (niters - peel_iters_prologue) % vf;
+	  /* If we need to peel for gaps, but no peeling is required, we have
+	     to peel VF iterations.  */
+	  if (LOOP_VINFO_PEELING_FOR_GAPS (loop_vinfo) && !peel_iters_epilogue)
+	    peel_iters_epilogue = vf;
 	}
     }
 
@@ -4212,7 +4217,8 @@ vect_transform_loop (loop_vec_info loop_vinfo)
   do_peeling_for_loop_bound
     = (!LOOP_VINFO_NITERS_KNOWN_P (loop_vinfo)
        || (LOOP_VINFO_NITERS_KNOWN_P (loop_vinfo)
-	   && LOOP_VINFO_INT_NITERS (loop_vinfo) % vectorization_factor != 0));
+	   && LOOP_VINFO_INT_NITERS (loop_vinfo) % vectorization_factor != 0)
+       || LOOP_VINFO_PEELING_FOR_GAPS (loop_vinfo));
 
   if (LOOP_REQUIRES_VERSIONING_FOR_ALIGNMENT (loop_vinfo)
       || LOOP_REQUIRES_VERSIONING_FOR_ALIAS (loop_vinfo))
