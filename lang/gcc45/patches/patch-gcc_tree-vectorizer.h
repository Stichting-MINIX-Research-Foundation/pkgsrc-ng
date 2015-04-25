$NetBSD$

--- gcc/tree-vectorizer.h.orig	Tue Nov  2 12:12:56 2010
+++ gcc/tree-vectorizer.h
@@ -242,6 +242,12 @@ typedef struct _loop_vec_info {
   /* The unrolling factor needed to SLP the loop. In case of that pure SLP is
      applied to the loop, i.e., no unrolling is needed, this is 1.  */
   unsigned slp_unrolling_factor;
+
+  /* When we have strided data accesses with gaps, we may introduce invalid
+     memory accesses.  We peel the last iteration of the loop to prevent
+     this.  */
+  bool peeling_for_gaps;
+
 } *loop_vec_info;
 
 /* Access Functions.  */
@@ -266,6 +272,7 @@ typedef struct _loop_vec_info {
 #define LOOP_VINFO_STRIDED_STORES(L)       (L)->strided_stores
 #define LOOP_VINFO_SLP_INSTANCES(L)        (L)->slp_instances
 #define LOOP_VINFO_SLP_UNROLLING_FACTOR(L) (L)->slp_unrolling_factor
+#define LOOP_VINFO_PEELING_FOR_GAPS(L)     (L)->peeling_for_gaps
 
 #define LOOP_REQUIRES_VERSIONING_FOR_ALIGNMENT(L) \
 VEC_length (gimple, (L)->may_misalign_stmts) > 0
