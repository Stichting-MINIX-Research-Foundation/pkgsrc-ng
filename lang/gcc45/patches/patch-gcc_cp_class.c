$NetBSD$

--- gcc/cp/class.c.orig	Fri Jul  9 19:50:25 2010
+++ gcc/cp/class.c
@@ -681,21 +681,10 @@ get_vtable_name (tree type)
    the abstract.  */
 
 void
-set_linkage_according_to_type (tree type, tree decl)
+set_linkage_according_to_type (tree type ATTRIBUTE_UNUSED, tree decl)
 {
-  /* If TYPE involves a local class in a function with internal
-     linkage, then DECL should have internal linkage too.  Other local
-     classes have no linkage -- but if their containing functions
-     have external linkage, it makes sense for DECL to have external
-     linkage too.  That will allow template definitions to be merged,
-     for example.  */
-  if (no_linkage_check (type, /*relaxed_p=*/true))
-    {
-      TREE_PUBLIC (decl) = 0;
-      DECL_INTERFACE_KNOWN (decl) = 1;
-    }
-  else
-    TREE_PUBLIC (decl) = 1;
+  TREE_PUBLIC (decl) = 1;
+  determine_visibility (decl);
 }
 
 /* Create a VAR_DECL for a primary or secondary vtable for CLASS_TYPE.
