$NetBSD$

--- gcc/varasm.c.orig	Tue Mar  8 13:03:34 2011
+++ gcc/varasm.c
@@ -30,6 +30,7 @@ along with GCC; see the file COPYING3.  If not see
 #include "config.h"
 #include "system.h"
 #include "coretypes.h"
+#include "pointer-set.h"
 #include "tm.h"
 #include "rtl.h"
 #include "tree.h"
@@ -2302,6 +2303,19 @@ contains_pointers_p (tree type)
    it all the way to final.  See PR 17982 for further discussion.  */
 static GTY(()) tree pending_assemble_externals;
 
+/* FIXME: Trunk is at GCC 4.8 now and the above problem still hasn't been
+   addressed properly.  This caused PR 52640 due to O(external_decls**2)
+   lookups in the pending_assemble_externals TREE_LIST in assemble_external.
+   Paper over with this pointer set, which we use to see if we have already
+   added a decl to pending_assemble_externals without first traversing
+   the entire pending_assemble_externals list.  See assemble_external().  */
+static struct pointer_set_t *pending_assemble_externals_set;
+
+/* Some targets delay some output to final using TARGET_ASM_FILE_END.
+   As a result, assemble_external can be called after the list of externals
+   is processed and the pointer set destroyed.  */
+static bool pending_assemble_externals_processed;
+
 #ifdef ASM_OUTPUT_EXTERNAL
 /* True if DECL is a function decl for which no out-of-line copy exists.
    It is assumed that DECL's assembler name has been set.  */
@@ -2351,6 +2365,8 @@ process_pending_assemble_externals (void)
     assemble_external_real (TREE_VALUE (list));
 
   pending_assemble_externals = 0;
+  pending_assemble_externals_processed = true;
+  pointer_set_destroy (pending_assemble_externals_set);
 #endif
 }
 
@@ -2391,7 +2407,13 @@ assemble_external (tree decl ATTRIBUTE_UNUSED)
     weak_decls = tree_cons (NULL, decl, weak_decls);
 
 #ifdef ASM_OUTPUT_EXTERNAL
-  if (value_member (decl, pending_assemble_externals) == NULL_TREE)
+  if (pending_assemble_externals_processed)
+    {
+      assemble_external_real (decl);
+      return;
+    }
+
+  if (! pointer_set_insert (pending_assemble_externals_set, decl))
     pending_assemble_externals = tree_cons (NULL, decl,
 					    pending_assemble_externals);
 #endif
@@ -5952,6 +5974,10 @@ init_varasm_once (void)
 
   if (readonly_data_section == NULL)
     readonly_data_section = text_section;
+
+#ifdef ASM_OUTPUT_EXTERNAL
+  pending_assemble_externals_set = pointer_set_create ();
+#endif
 }
 
 enum tls_model
