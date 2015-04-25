$NetBSD$

--- gcc/config/darwin.c.orig	Thu Jun 24 21:06:37 2010
+++ gcc/config/darwin.c
@@ -337,6 +337,34 @@ static GTY ((param_is (struct machopic_indirection))) 
 
 /* Return a hash value for a SLOT in the indirections hash table.  */
 
+void
+darwin_rename_builtins (void)
+{
+  /* The system ___divdc3 routine in libSystem on darwin10 is not
+     accurate to 1ulp, ours is, so we avoid ever using the system name
+     for this routine and instead install a non-conflicting name that
+     is accurate.
+
+     When -ffast-math or -funsafe-math-optimizations is given, we can
+     use the faster version.  */
+  if (!flag_unsafe_math_optimizations)
+    {
+      int dcode = (BUILT_IN_COMPLEX_DIV_MIN
+		   + DCmode - MIN_MODE_COMPLEX_FLOAT);
+      tree fn = built_in_decls[dcode];
+      /* Fortran and c call TARGET_INIT_BUILTINS and
+	 TARGET_INIT_LIBFUNCS at different times, so we have to put a
+	 call into each to ensure that at least one of them is called
+	 after build_common_builtin_nodes.  A better fix is to add a
+	 new hook to run after build_common_builtin_nodes runs.  */
+      if (fn)
+	set_user_assembler_name (fn, "___ieee_divdc3");
+      fn = implicit_built_in_decls[dcode];
+      if (fn)
+	set_user_assembler_name (fn, "___ieee_divdc3");
+    }
+}
+
 static hashval_t
 machopic_indirection_hash (const void *slot)
 {
