$NetBSD$

--- gcc/tree-mudflap.c.orig	Wed Nov 25 10:55:54 2009
+++ gcc/tree-mudflap.c
@@ -72,6 +72,13 @@ static tree mx_xfn_xform_decls (gimple_stmt_iterator *
 static gimple_seq mx_register_decls (tree, gimple_seq, location_t);
 static unsigned int execute_mudflap_function_decls (void);
 
+/* Return true if DECL is artificial stub that shouldn't be instrumented by
+   mf.  We should instrument clones of non-artificial functions.  */
+static inline bool
+mf_artificial (const_tree decl)
+{
+  return DECL_ARTIFICIAL (DECL_ORIGIN (decl));
+}
 
 /* ------------------------------------------------------------------------ */
 /* Some generally helpful functions for mudflap instrumentation.  */
@@ -437,8 +444,8 @@ execute_mudflap_function_ops (void)
 
   /* Don't instrument functions such as the synthetic constructor
      built during mudflap_finish_file.  */
-  if (mf_marked_p (current_function_decl) ||
-      DECL_ARTIFICIAL (current_function_decl))
+  if (mf_marked_p (current_function_decl)
+      || mf_artificial (current_function_decl))
     return 0;
 
   push_gimplify_context (&gctx);
@@ -1026,8 +1033,8 @@ execute_mudflap_function_decls (void)
 
   /* Don't instrument functions such as the synthetic constructor
      built during mudflap_finish_file.  */
-  if (mf_marked_p (current_function_decl) ||
-      DECL_ARTIFICIAL (current_function_decl))
+  if (mf_marked_p (current_function_decl)
+      || mf_artificial (current_function_decl))
     return 0;
 
   push_gimplify_context (&gctx);
@@ -1109,7 +1116,7 @@ mx_register_decls (tree decl, gimple_seq seq, location
           /* Add the __mf_register call at the current appending point.  */
           if (gsi_end_p (initially_stmts))
 	    {
-	      if (!DECL_ARTIFICIAL (decl))
+	      if (!mf_artificial (decl))
 		warning (OPT_Wmudflap,
 			 "mudflap cannot track %qE in stub function",
 			 DECL_NAME (decl));
@@ -1280,7 +1287,7 @@ mudflap_enqueue_decl (tree obj)
      during mudflap_finish_file ().  That would confuse the user,
      since the text would refer to variables that don't show up in the
      user's source code.  */
-  if (DECL_P (obj) && DECL_EXTERNAL (obj) && DECL_ARTIFICIAL (obj))
+  if (DECL_P (obj) && DECL_EXTERNAL (obj) && mf_artificial (obj))
     return;
 
   VEC_safe_push (tree, gc, deferred_static_decls, obj);
