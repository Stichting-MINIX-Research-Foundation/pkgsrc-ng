$NetBSD$

--- gcc/cp/decl2.c.orig	Thu Apr 21 02:56:39 2011
+++ gcc/cp/decl2.c
@@ -1189,9 +1189,9 @@ save_template_attributes (tree *attr_p, tree *decl_p)
 
   old_attrs = *q;
 
-  /* Place the late attributes at the beginning of the attribute
+  /* Merge the late attributes at the beginning with the attribute
      list.  */
-  TREE_CHAIN (tree_last (late_attrs)) = *q;
+  late_attrs = merge_attributes (late_attrs, *q);
   *q = late_attrs;
 
   if (!DECL_P (*decl_p) && *decl_p == TYPE_MAIN_VARIANT (*decl_p))
@@ -3991,8 +3991,6 @@ possibly_inlined_p (tree decl)
 void
 mark_used (tree decl)
 {
-  HOST_WIDE_INT saved_processing_template_decl = 0;
-
   /* If DECL is a BASELINK for a single function, then treat it just
      like the DECL for the function.  Otherwise, if the BASELINK is
      for an overloaded function, we don't know which function was
@@ -4029,9 +4027,6 @@ mark_used (tree decl)
       error ("used here");
       return;
     }
-  /* If we don't need a value, then we don't need to synthesize DECL.  */
-  if (cp_unevaluated_operand != 0)
-    return;
 
   /* We can only check DECL_ODR_USED on variables or functions with
      DECL_LANG_SPECIFIC set, and these are also the only decls that we
@@ -4059,9 +4054,10 @@ mark_used (tree decl)
      DECL.  However, if DECL is a static data member initialized with
      a constant, we need the value right now because a reference to
      such a data member is not value-dependent.  */
-  if (TREE_CODE (decl) == VAR_DECL
-      && DECL_INITIALIZED_BY_CONSTANT_EXPRESSION_P (decl)
-      && DECL_CLASS_SCOPE_P (decl))
+  if (DECL_INTEGRAL_CONSTANT_VAR_P (decl)
+      && !DECL_INITIAL (decl)
+      && DECL_LANG_SPECIFIC (decl)
+      && DECL_TEMPLATE_INSTANTIATION (decl))
     {
       /* Don't try to instantiate members of dependent types.  We
 	 cannot just use dependent_type_p here because this function
@@ -4071,12 +4067,14 @@ mark_used (tree decl)
       if (CLASSTYPE_TEMPLATE_INFO ((DECL_CONTEXT (decl)))
 	  && uses_template_parms (CLASSTYPE_TI_ARGS (DECL_CONTEXT (decl))))
 	return;
-      /* Pretend that we are not in a template, even if we are, so
-	 that the static data member initializer will be processed.  */
-      saved_processing_template_decl = processing_template_decl;
-      processing_template_decl = 0;
+      instantiate_decl (decl, /*defer_ok=*/false,
+			/*expl_inst_class_mem_p=*/false);
     }
 
+  /* If we don't need a value, then we don't need to synthesize DECL.  */
+  if (cp_unevaluated_operand != 0)
+    return;
+
   if (processing_template_decl)
     return;
 
@@ -4149,8 +4147,6 @@ mark_used (tree decl)
        need.  Therefore, we always try to defer instantiation.  */
     instantiate_decl (decl, /*defer_ok=*/true,
 		      /*expl_inst_class_mem_p=*/false);
-
-  processing_template_decl = saved_processing_template_decl;
 }
 
 #include "gt-cp-decl2.h"
