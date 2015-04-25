$NetBSD$

--- gcc/cp/mangle.c.orig	Tue Mar  8 17:40:27 2011
+++ gcc/cp/mangle.c
@@ -1778,11 +1778,6 @@ write_type (tree type)
   if (find_substitution (type))
     return;
 
-  /* According to the C++ ABI, some library classes are passed the
-     same as the scalar type of their single member and use the same
-     mangling.  */
-  if (TREE_CODE (type) == RECORD_TYPE && TYPE_TRANSPARENT_AGGR (type))
-    type = TREE_TYPE (first_field (type));
 
   if (write_CV_qualifiers_for_type (type) > 0)
     /* If TYPE was CV-qualified, we just wrote the qualifiers; now
@@ -1801,6 +1796,12 @@ write_type (tree type)
 
       /* See through any typedefs.  */
       type = TYPE_MAIN_VARIANT (type);
+
+      /* According to the C++ ABI, some library classes are passed the
+	 same as the scalar type of their single member and use the same
+	 mangling.  */
+      if (TREE_CODE (type) == RECORD_TYPE && TYPE_TRANSPARENT_AGGR (type))
+	type = TREE_TYPE (first_field (type));
 
       if (TYPE_PTRMEM_P (type))
 	write_pointer_to_member_type (type);
