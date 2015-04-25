$NetBSD$

--- gcc/c-lex.c.orig	Thu Apr  7 18:24:43 2011
+++ gcc/c-lex.c
@@ -718,22 +718,25 @@ interpret_float (const cpp_token *token, unsigned int 
      outside the range of representable values of its type.  Since we
      have __builtin_inf* to produce an infinity, this is now a
      mandatory pedwarn if the target does not support infinities.  */
-  if (REAL_VALUE_ISINF (real)
-      || (const_type != type && REAL_VALUE_ISINF (real_trunc)))
+  if (warn_overflow)
     {
-      if (!MODE_HAS_INFINITIES (TYPE_MODE (type)))
-	pedwarn (input_location, 0, "floating constant exceeds range of %qT", type);
-      else
-	warning (OPT_Woverflow, "floating constant exceeds range of %qT", type);
-    }
-  /* We also give a warning if the value underflows.  */
-  else if (REAL_VALUES_EQUAL (real, dconst0)
-	   || (const_type != type && REAL_VALUES_EQUAL (real_trunc, dconst0)))
-    {
-      REAL_VALUE_TYPE realvoidmode;
-      int overflow = real_from_string (&realvoidmode, copy);
-      if (overflow < 0 || !REAL_VALUES_EQUAL (realvoidmode, dconst0))
-	warning (OPT_Woverflow, "floating constant truncated to zero");
+      if (REAL_VALUE_ISINF (real)
+          || (const_type != type && REAL_VALUE_ISINF (real_trunc)))
+        {
+	  if (!MODE_HAS_INFINITIES (TYPE_MODE (type)))
+	    pedwarn (input_location, 0, "floating constant exceeds range of %qT", type);
+	  else
+	    warning (OPT_Woverflow, "floating constant exceeds range of %qT", type);
+	}
+      /* We also give a warning if the value underflows.  */
+      else if (REAL_VALUES_EQUAL (real, dconst0)
+	       || (const_type != type && REAL_VALUES_EQUAL (real_trunc, dconst0)))
+	{
+	  REAL_VALUE_TYPE realvoidmode;
+	  int overflow = real_from_string (&realvoidmode, copy);
+	  if (overflow < 0 || !REAL_VALUES_EQUAL (realvoidmode, dconst0))
+	    warning (OPT_Woverflow, "floating constant truncated to zero");
+	}
     }
 
   /* Create a node with determined type and value.  */
