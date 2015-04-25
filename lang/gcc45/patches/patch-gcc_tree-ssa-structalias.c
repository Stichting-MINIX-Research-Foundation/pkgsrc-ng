$NetBSD$

--- gcc/tree-ssa-structalias.c.orig	Tue Mar  8 13:31:13 2011
+++ gcc/tree-ssa-structalias.c
@@ -266,6 +266,7 @@ static varinfo_t first_vi_for_offset (varinfo_t, unsig
 static varinfo_t first_or_preceding_vi_for_offset (varinfo_t,
 						   unsigned HOST_WIDE_INT);
 static varinfo_t lookup_vi_for_tree (tree);
+static inline bool type_can_have_subvars (const_tree);
 
 /* Pool of variable info structures.  */
 static alloc_pool variable_info_pool;
@@ -3187,10 +3188,51 @@ get_constraint_for_1 (tree t, VEC (ce_s, heap) **resul
 	  {
 	  case INDIRECT_REF:
 	    {
+	      struct constraint_expr cs;
+	      varinfo_t vi, curr;
 	      get_constraint_for_1 (TREE_OPERAND (t, 0), results, address_p,
 				    lhs_p);
 	      do_deref (results);
-	      return;
+
+	      /* If we are not taking the address then make sure to process
+		 all subvariables we might access.  */
+	      if (address_p)
+		return;
+
+	      cs = *VEC_last (ce_s, *results);
+	      if (cs.type == DEREF
+		  && type_can_have_subvars (TREE_TYPE (t)))
+		{
+		  /* For dereferences this means we have to defer it
+		     to solving time.  */
+		  VEC_last (ce_s, *results)->offset = UNKNOWN_OFFSET;
+		  return;
+		}
+	      if (cs.type != SCALAR)
+		return;
+
+	      vi = get_varinfo (cs.var);
+	      curr = vi->next;
+	      if (!vi->is_full_var
+		  && curr)
+		{
+		  unsigned HOST_WIDE_INT size;
+		  if (host_integerp (TYPE_SIZE (TREE_TYPE (t)), 1))
+		    size = TREE_INT_CST_LOW (TYPE_SIZE (TREE_TYPE (t)));
+		  else
+		    size = -1;
+		  for (; curr; curr = curr->next)
+		    {
+		      if (curr->offset - vi->offset < size)
+			{
+			  cs.var = curr->id;
+			  VEC_safe_push (ce_s, heap, *results, &cs);
+			}
+		      else
+			break;
+		    }
+                }
+              return;
 	    }
 	  case ARRAY_REF:
 	  case ARRAY_RANGE_REF:
@@ -3968,15 +4010,6 @@ find_func_aliases (gimple origt)
 	  && DECL_P (lhsop)
 	  && is_global_var (lhsop))
 	make_escape_constraint (rhsop);
-      /* If this is a conversion of a non-restrict pointer to a
-	 restrict pointer track it with a new heapvar.  */
-      else if (gimple_assign_cast_p (t)
-	       && POINTER_TYPE_P (TREE_TYPE (rhsop))
-	       && POINTER_TYPE_P (TREE_TYPE (lhsop))
-	       && !TYPE_RESTRICT (TREE_TYPE (rhsop))
-	       && TYPE_RESTRICT (TREE_TYPE (lhsop)))
-	make_constraint_from_restrict (get_vi_for_tree (lhsop),
-				       "CAST_RESTRICT");
     }
   /* Handle escapes through return.  */
   else if (gimple_code (t) == GIMPLE_RETURN
@@ -4210,6 +4243,15 @@ sort_fieldstack (VEC(fieldoff_s,heap) *fieldstack)
 	 fieldoff_compare);
 }
 
+/* Return true if T is a type that can have subvars.  */
+
+static inline bool
+type_can_have_subvars (const_tree t)
+{
+  /* Aggregates without overlapping fields can have subvars.  */
+  return TREE_CODE (t) == RECORD_TYPE;
+}
+
 /* Return true if V is a tree that we can have subvars for.
    Normally, this is any aggregate type.  Also complex
    types which are not gimple registers can have subvars.  */
@@ -4225,11 +4267,7 @@ var_can_have_subvars (const_tree v)
   if (!DECL_P (v))
     return false;
 
-  /* Aggregates without overlapping fields can have subvars.  */
-  if (TREE_CODE (TREE_TYPE (v)) == RECORD_TYPE)
-    return true;
-
-  return false;
+  return type_can_have_subvars (TREE_TYPE (v));
 }
 
 /* Return true if T is a type that does contain pointers.  */
