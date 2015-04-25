$NetBSD$

--- gcc/config/i386/winnt-cxx.c.orig	Wed Oct  7 02:57:21 2009
+++ gcc/config/i386/winnt-cxx.c
@@ -101,6 +101,20 @@ i386_pe_adjust_class_at_definition (tree t)
  
   if (lookup_attribute ("dllexport", TYPE_ATTRIBUTES (t)) != NULL_TREE)
     {
+      tree tmv = TYPE_MAIN_VARIANT (t);
+
+      /* Make sure that we set dllexport attribute to typeinfo's
+	 base declaration, as otherwise it would fail to be exported as
+	 it isn't a class-member.  */
+      if (tmv != NULL_TREE
+	  && CLASSTYPE_TYPEINFO_VAR (tmv) != NULL_TREE)
+	{
+	  tree na, ti_decl = CLASSTYPE_TYPEINFO_VAR (tmv);
+	  na = tree_cons (get_identifier ("dllexport"), NULL_TREE,
+			  NULL_TREE);
+	  decl_attributes (&ti_decl, na, 0);
+	}
+
       /* Check static VAR_DECL's.  */
       for (member = TYPE_FIELDS (t); member; member = TREE_CHAIN (member))
 	if (TREE_CODE (member) == VAR_DECL)     
