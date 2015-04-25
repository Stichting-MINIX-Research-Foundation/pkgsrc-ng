$NetBSD$

--- libobjc/hash.c.orig	Thu Apr  9 15:00:19 2009
+++ libobjc/hash.c
@@ -151,8 +151,8 @@ objc_hash_add (cache_ptr *cachep, const void *key, voi
 				   (*cachep)->hash_func,
 				   (*cachep)->compare_func);
 
-    DEBUG_PRINTF ("Expanding cache %#x from %d to %d\n",
-		  (int) *cachep, (*cachep)->size, new->size);
+    DEBUG_PRINTF ("Expanding cache %p from %d to %d\n",
+		  *cachep, (*cachep)->size, new->size);
 
     /* Copy the nodes from the first hash table to the new one.  */
     while ((node1 = objc_hash_next (*cachep, node1)))
