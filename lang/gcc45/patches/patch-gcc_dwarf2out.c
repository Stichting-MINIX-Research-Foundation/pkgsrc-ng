$NetBSD$

--- gcc/dwarf2out.c.orig	Mon Apr 18 17:38:13 2011
+++ gcc/dwarf2out.c
@@ -4254,6 +4254,12 @@ typedef struct GTY(()) dw_loc_list_struct {
 		      Only on head of list */
   const char *section; /* Section this loclist is relative to */
   dw_loc_descr_ref expr;
+  /* True if all addresses in this and subsequent lists are known to be
+     resolved.  */
+  bool resolved_addr;
+  /* True if this list has been replaced by dw_loc_next.  */
+  bool replaced;
+  bool emitted;
 } dw_loc_list_node;
 
 #if defined (DWARF2_DEBUGGING_INFO) || defined (DWARF2_UNWIND_INFO)
@@ -5757,6 +5763,19 @@ typedef struct var_loc_list_def var_loc_list;
 /* Table of decl location linked lists.  */
 static GTY ((param_is (var_loc_list))) htab_t decl_loc_table;
 
+/* A cached location list.  */
+struct GTY (()) cached_dw_loc_list_def {
+  /* The DECL_UID of the decl that this entry describes.  */
+  unsigned int decl_id;
+
+  /* The cached location list.  */
+  dw_loc_list_ref loc_list;
+};
+typedef struct cached_dw_loc_list_def cached_dw_loc_list;
+
+/* Table of cached location lists.  */
+static GTY ((param_is (cached_dw_loc_list))) htab_t cached_dw_loc_list_table;
+
 /* A pointer to the base of a list of references to DIE's that
    are uniquely identified by their tag, presence/absence of
    children DIE's, and list of attribute/value pairs.  */
@@ -6110,7 +6129,7 @@ static bool add_const_value_attribute (dw_die_ref, rtx
 static void insert_int (HOST_WIDE_INT, unsigned, unsigned char *);
 static void insert_float (const_rtx, unsigned char *);
 static rtx rtl_for_decl_location (tree);
-static bool add_location_or_const_value_attribute (dw_die_ref, tree,
+static bool add_location_or_const_value_attribute (dw_die_ref, tree, bool,
 						   enum dwarf_attribute);
 static bool tree_add_const_value_attribute (dw_die_ref, tree);
 static bool tree_add_const_value_attribute_for_decl (dw_die_ref, tree);
@@ -7729,6 +7748,24 @@ lookup_decl_loc (const_tree decl)
     htab_find_with_hash (decl_loc_table, decl, DECL_UID (decl));
 }
 
+/* Returns a hash value for X (which really is a cached_dw_loc_list_list).  */
+
+static hashval_t
+cached_dw_loc_list_table_hash (const void *x)
+{
+  return (hashval_t) ((const cached_dw_loc_list *) x)->decl_id;
+}
+
+/* Return nonzero if decl_id of cached_dw_loc_list X is the same as
+   UID of decl *Y.  */
+
+static int
+cached_dw_loc_list_table_eq (const void *x, const void *y)
+{
+  return (((const cached_dw_loc_list *) x)->decl_id
+	  == DECL_UID ((const_tree) y));
+}
+
 /* Equate a DIE to a particular declaration.  */
 
 static void
@@ -10353,6 +10390,10 @@ output_loc_list (dw_loc_list_ref list_head)
 {
   dw_loc_list_ref curr = list_head;
 
+  if (list_head->emitted)
+    return;
+  list_head->emitted = true;
+
   ASM_OUTPUT_LABEL (asm_out_file, list_head->ll_symbol);
 
   /* Walk the location list, and output each range + expression.  */
@@ -15918,15 +15959,22 @@ fortran_common (tree decl, HOST_WIDE_INT *value)
    these things can crop up in other ways also.)  Note that one type of
    constant value which can be passed into an inlined function is a constant
    pointer.  This can happen for example if an actual argument in an inlined
-   function call evaluates to a compile-time constant address.  */
+   function call evaluates to a compile-time constant address.
 
+   CACHE_P is true if it is worth caching the location list for DECL,
+   so that future calls can reuse it rather than regenerate it from scratch.
+   This is true for BLOCK_NONLOCALIZED_VARS in inlined subroutines,
+   since we will need to refer to them each time the function is inlined.  */
+
 static bool
-add_location_or_const_value_attribute (dw_die_ref die, tree decl,
+add_location_or_const_value_attribute (dw_die_ref die, tree decl, bool cache_p,
 				       enum dwarf_attribute attr)
 {
   rtx rtl;
   dw_loc_list_ref list;
   var_loc_list *loc_list;
+  cached_dw_loc_list *cache;
+  void **slot;
 
   if (TREE_CODE (decl) == ERROR_MARK)
     return false;
@@ -15962,7 +16010,34 @@ add_location_or_const_value_attribute (dw_die_ref die,
 	  && add_const_value_attribute (die, rtl))
 	 return true;
     }
-  list = loc_list_from_tree (decl, decl_by_reference_p (decl) ? 0 : 2);
+  /* If this decl is from BLOCK_NONLOCALIZED_VARS, we might need its
+     list several times.  See if we've already cached the contents.  */
+  list = NULL;
+  if (loc_list == NULL || cached_dw_loc_list_table == NULL)
+    cache_p = false;
+  if (cache_p)
+    {
+      cache = (cached_dw_loc_list *)
+	htab_find_with_hash (cached_dw_loc_list_table, decl, DECL_UID (decl));
+      if (cache)
+	list = cache->loc_list;
+    }
+  if (list == NULL)
+    {
+      list = loc_list_from_tree (decl, decl_by_reference_p (decl) ? 0 : 2);
+      /* It is usually worth caching this result if the decl is from
+	 BLOCK_NONLOCALIZED_VARS and if the list has at least two elements.  */
+      if (cache_p && list && list->dw_loc_next)
+	{
+	  slot = htab_find_slot_with_hash (cached_dw_loc_list_table, decl,
+					   DECL_UID (decl), INSERT);
+	  cache = (cached_dw_loc_list *)
+	    ggc_alloc_cleared (sizeof (cached_dw_loc_list));
+	  cache->decl_id = DECL_UID (decl);
+	  cache->loc_list = list;
+	  *slot = cache;
+	}
+    }
   if (list)
     {
       add_AT_location_description (die, attr, list);
@@ -16592,9 +16667,9 @@ add_byte_size_attribute (dw_die_ref die, tree tree_nod
 
   /* Note that `size' might be -1 when we get to this point.  If it is, that
      indicates that the byte size of the entity in question is variable.  We
-     have no good way of expressing this fact in Dwarf at the present time,
-     so just let the -1 pass on through.  */
-  add_AT_unsigned (die, DW_AT_byte_size, size);
+     have no good way of expressing this fact in Dwarf at the present time.
+     GCC/35998: Avoid passing negative size values to Dtrace and gdb. */
+  add_AT_unsigned (die, DW_AT_byte_size, (size != (unsigned)-1 ? size : 0));
 }
 
 /* For a FIELD_DECL node which represents a bit-field, output an attribute
@@ -17530,7 +17605,7 @@ gen_formal_parameter_die (tree node, tree origin, bool
         equate_decl_number_to_die (node, parm_die);
       if (! DECL_ABSTRACT (node_or_origin))
 	add_location_or_const_value_attribute (parm_die, node_or_origin,
-					       DW_AT_location);
+					       node == NULL, DW_AT_location);
 
       break;
 
@@ -17710,6 +17785,7 @@ dwarf2out_abstract_function (tree decl)
   tree context;
   int was_abstract;
   htab_t old_decl_loc_table;
+  htab_t old_cached_dw_loc_list_table;
 
   /* Make sure we have the actual abstract inline, not a clone.  */
   decl = DECL_ORIGIN (decl);
@@ -17723,7 +17799,9 @@ dwarf2out_abstract_function (tree decl)
      DIE.  Be sure to not clobber the outer location table nor use it or we would
      get locations in abstract instantces.  */
   old_decl_loc_table = decl_loc_table;
+  old_cached_dw_loc_list_table = cached_dw_loc_list_table;
   decl_loc_table = NULL;
+  cached_dw_loc_list_table = NULL;
 
   /* Be sure we've emitted the in-class declaration DIE (if any) first, so
      we don't get confused by DECL_ABSTRACT.  */
@@ -17748,6 +17826,7 @@ dwarf2out_abstract_function (tree decl)
 
   current_function_decl = save_fn;
   decl_loc_table = old_decl_loc_table;
+  cached_dw_loc_list_table = old_cached_dw_loc_list_table;
   pop_cfun ();
 }
 
@@ -18429,9 +18508,8 @@ gen_variable_die (tree decl, tree origin, dw_die_ref c
           && !TREE_SYMBOL_REFERENCED (DECL_ASSEMBLER_NAME (decl_or_origin)))
 	defer_location (decl_or_origin, var_die);
       else
-        add_location_or_const_value_attribute (var_die,
-					       decl_or_origin,
-					       DW_AT_location);
+        add_location_or_const_value_attribute (var_die, decl_or_origin,
+					       decl == NULL, DW_AT_location);
       add_pubname (decl_or_origin, var_die);
     }
   else
@@ -20037,6 +20115,7 @@ dwarf2out_function_decl (tree decl)
   dwarf2out_decl (decl);
 
   htab_empty (decl_loc_table);
+  htab_empty (cached_dw_loc_list_table);
 }
 
 /* Output a marker (i.e. a label) for the beginning of the generated code for
@@ -20637,6 +20716,11 @@ dwarf2out_init (const char *filename ATTRIBUTE_UNUSED)
   decl_loc_table = htab_create_ggc (10, decl_loc_table_hash,
 				    decl_loc_table_eq, NULL);
 
+  /* Allocate the cached_dw_loc_list_table.  */
+  cached_dw_loc_list_table
+    = htab_create_ggc (10, cached_dw_loc_list_table_hash,
+		       cached_dw_loc_list_table_eq, NULL);
+
   /* Allocate the initial hunk of the decl_scope_table.  */
   decl_scope_table = VEC_alloc (tree, gc, 256);
 
@@ -21261,30 +21345,53 @@ resolve_addr (dw_die_ref die)
 {
   dw_die_ref c;
   dw_attr_ref a;
-  dw_loc_list_ref *curr;
+  dw_loc_list_ref *curr, *start, loc;
   unsigned ix;
 
   for (ix = 0; VEC_iterate (dw_attr_node, die->die_attr, ix, a); ix++)
     switch (AT_class (a))
       {
       case dw_val_class_loc_list:
-	curr = AT_loc_list_ptr (a);
-	while (*curr)
+	start = curr = AT_loc_list_ptr (a);
+	loc = *curr;
+	gcc_assert (loc);
+	/* The same list can be referenced more than once.  See if we have
+	   already recorded the result from a previous pass.  */
+	if (loc->replaced)
+	  *curr = loc->dw_loc_next;
+	else if (!loc->resolved_addr)
 	  {
-	    if (!resolve_addr_in_expr ((*curr)->expr))
+	    /* As things stand, we do not expect or allow one die to
+	       reference a suffix of another die's location list chain.
+	       References must be identical or completely separate.
+	       There is therefore no need to cache the result of this
+	       pass on any list other than the first; doing so
+	       would lead to unnecessary writes.  */
+	    while (*curr)
 	      {
-		dw_loc_list_ref next = (*curr)->dw_loc_next;
-		if (next && (*curr)->ll_symbol)
+		gcc_assert (!(*curr)->replaced && !(*curr)->resolved_addr);
+		if (!resolve_addr_in_expr ((*curr)->expr))
 		  {
-		    gcc_assert (!next->ll_symbol);
-		    next->ll_symbol = (*curr)->ll_symbol;
+		    dw_loc_list_ref next = (*curr)->dw_loc_next;
+		    if (next && (*curr)->ll_symbol)
+		      {
+			gcc_assert (!next->ll_symbol);
+			next->ll_symbol = (*curr)->ll_symbol;
+		      }
+		    *curr = next;
 		  }
-		*curr = next;
+		else
+		  curr = &(*curr)->dw_loc_next;
 	      }
+	    if (loc == *start)
+	      loc->resolved_addr = 1;
 	    else
-	      curr = &(*curr)->dw_loc_next;
+	      {
+		loc->replaced = 1;
+		loc->dw_loc_next = *start;
+	      }
 	  }
-	if (!AT_loc_list (a))
+	if (!*start)
 	  {
 	    remove_AT (die, a->dw_attr);
 	    ix--;
@@ -21344,6 +21451,7 @@ dwarf2out_finish (const char *filename)
       add_location_or_const_value_attribute (
         VEC_index (deferred_locations, deferred_locations_list, i)->die,
         VEC_index (deferred_locations, deferred_locations_list, i)->variable,
+	false,
 	DW_AT_location);
     }
 
