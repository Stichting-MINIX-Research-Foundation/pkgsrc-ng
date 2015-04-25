$NetBSD$

--- gcc/lto-streamer-out.c.orig	Fri May 28 19:02:24 2010
+++ gcc/lto-streamer-out.c
@@ -2302,7 +2302,7 @@ write_symbol_vec (struct lto_streamer_cache_d *cache,
       enum gcc_plugin_symbol_kind kind;
       enum gcc_plugin_symbol_visibility visibility;
       int slot_num;
-      uint64_t size;
+      unsigned HOST_WIDEST_INT size;
       const char *comdat;
 
       /* None of the following kinds of symbols are needed in the
@@ -2367,10 +2367,9 @@ write_symbol_vec (struct lto_streamer_cache_d *cache,
 	}
 
       if (kind == GCCPK_COMMON
-	  && DECL_SIZE (t)
-	  && TREE_CODE (DECL_SIZE (t)) == INTEGER_CST)
-	size = (((uint64_t) TREE_INT_CST_HIGH (DECL_SIZE (t))) << 32)
-	  | TREE_INT_CST_LOW (DECL_SIZE (t));
+	  && DECL_SIZE_UNIT (t)
+	  && TREE_CODE (DECL_SIZE_UNIT (t)) == INTEGER_CST)
+	size = TREE_INT_CST_LOW (DECL_SIZE_UNIT (t));
       else
 	size = 0;
 
