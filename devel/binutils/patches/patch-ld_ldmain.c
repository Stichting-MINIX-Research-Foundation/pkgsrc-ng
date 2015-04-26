$NetBSD$

--- ld/ldmain.c.orig	Mon Mar 25 08:06:23 2013
+++ ld/ldmain.c
@@ -642,6 +642,23 @@ add_ysym (const char *name)
     einfo (_("%P%F: bfd_hash_lookup failed: %E\n"));
 }
 
+void
+add_ignoresym (const char *name)
+{
+  if (link_info.ignore_hash == NULL)
+    {
+      link_info.ignore_hash = xmalloc (sizeof (struct bfd_hash_table));
+      if (! bfd_hash_table_init_n (link_info.ignore_hash,
+				   bfd_hash_newfunc,
+				   sizeof (struct bfd_hash_entry),
+				   61))
+	einfo (_("%P%F: bfd_hash_table_init failed: %E\n"));
+    }
+
+  if (bfd_hash_lookup (link_info.ignore_hash, name, TRUE, TRUE) == NULL)
+    einfo (_("%P%F: bfd_hash_lookup failed: %E\n"));
+}
+
 /* Record a symbol to be wrapped, from the --wrap option.  */
 
 void
@@ -1239,24 +1256,25 @@ undefined_symbol (struct bfd_link_info *info ATTRIBUTE
 
 #define MAX_ERRORS_IN_A_ROW 5
 
+  if (info->ignore_hash != NULL
+      && bfd_hash_lookup (info->ignore_hash, name, FALSE, FALSE) != NULL)
+    return TRUE;
+
   if (config.warn_once)
     {
-      static struct bfd_hash_table *hash;
-
       /* Only warn once about a particular undefined symbol.  */
-      if (hash == NULL)
+      if (info->ignore_hash == NULL)
 	{
-	  hash = (struct bfd_hash_table *)
-              xmalloc (sizeof (struct bfd_hash_table));
-	  if (!bfd_hash_table_init (hash, bfd_hash_newfunc,
+	  info->ignore_hash = xmalloc (sizeof (struct bfd_hash_table));
+	  if (!bfd_hash_table_init (info->ignore_hash, bfd_hash_newfunc,
 				    sizeof (struct bfd_hash_entry)))
 	    einfo (_("%F%P: bfd_hash_table_init failed: %E\n"));
 	}
 
-      if (bfd_hash_lookup (hash, name, FALSE, FALSE) != NULL)
+      if (bfd_hash_lookup (info->ignore_hash, name, FALSE, FALSE) != NULL)
 	return TRUE;
 
-      if (bfd_hash_lookup (hash, name, TRUE, TRUE) == NULL)
+      if (bfd_hash_lookup (info->ignore_hash, name, TRUE, TRUE) == NULL)
 	einfo (_("%F%P: bfd_hash_lookup failed: %E\n"));
     }
 
