$NetBSD$

--- gcc/cp/decl.c.orig	Wed Apr 20 00:06:19 2011
+++ gcc/cp/decl.c
@@ -12877,8 +12877,17 @@ cxx_maybe_build_cleanup (tree decl)
 	cleanup = call;
     }
 
+  /* build_delete sets the location of the destructor call to the
+     current location, even though the destructor is going to be
+     called later, at the end of the current scope.  This can lead to
+     a "jumpy" behaviour for users of debuggers when they step around
+     the end of the block.  So let's unset the location of the
+     destructor call instead.  */
+  if (cleanup != NULL && EXPR_P (cleanup))
+    SET_EXPR_LOCATION (cleanup, UNKNOWN_LOCATION);
   return cleanup;
 }
+
 
 /* When a stmt has been parsed, this function is called.  */
 
