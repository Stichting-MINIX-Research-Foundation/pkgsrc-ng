$NetBSD$

--- gcc/cfgexpand.c.orig	Sun Jan 16 20:20:21 2011
+++ gcc/cfgexpand.c
@@ -1080,7 +1080,9 @@ stack_protect_classify_type (tree type)
 	  else
 	    len = tree_low_cst (TYPE_SIZE_UNIT (type), 1);
 
-	  if (len < max)
+	  if (len == 0)
+	    ret = SPCT_HAS_ARRAY;
+	  else if (len < max)
 	    ret = SPCT_HAS_SMALL_CHAR_ARRAY | SPCT_HAS_ARRAY;
 	  else
 	    ret = SPCT_HAS_LARGE_CHAR_ARRAY | SPCT_HAS_ARRAY;
@@ -2974,7 +2976,7 @@ expand_debug_expr (tree exp)
 
 	    gcc_assert (part >= 0 && (unsigned)part < SA.map->num_partitions);
 
-	    op0 = SA.partition_to_pseudo[part];
+	    op0 = copy_rtx (SA.partition_to_pseudo[part]);
 	  }
 	goto adjust_mode;
       }
