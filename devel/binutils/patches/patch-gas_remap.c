$NetBSD$

--- gas/remap.c.orig	Fri Mar 11 14:18:24 2011
+++ gas/remap.c
@@ -84,8 +84,8 @@ remap_debug_filename (const char *filename)
     return xstrdup (filename);
   name = filename + map->old_len;
   name_len = strlen (name) + 1;
-  s = (char *) alloca (name_len + map->new_len);
+  s = (char *) xmalloc (name_len + map->new_len);
   memcpy (s, map->new_prefix, map->new_len);
   memcpy (s + map->new_len, name, name_len);
-  return xstrdup (s);
+  return s;
 }
