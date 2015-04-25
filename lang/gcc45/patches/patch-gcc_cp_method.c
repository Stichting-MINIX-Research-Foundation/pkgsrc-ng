$NetBSD$

--- gcc/cp/method.c.orig	Sat Mar 20 08:55:32 2010
+++ gcc/cp/method.c
@@ -374,6 +374,7 @@ use_thunk (tree thunk_fndecl, bool emit_p)
       DECL_CONTEXT (x) = thunk_fndecl;
       SET_DECL_RTL (x, NULL_RTX);
       DECL_HAS_VALUE_EXPR_P (x) = 0;
+      TREE_ADDRESSABLE (x) = 0;
       t = x;
     }
   a = nreverse (t);
