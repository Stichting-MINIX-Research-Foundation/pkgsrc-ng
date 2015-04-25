$NetBSD$

--- gcc/tree-vect-stmts.c.orig	Thu Mar  3 12:22:10 2011
+++ gcc/tree-vect-stmts.c
@@ -1416,7 +1416,7 @@ vectorizable_call (gimple stmt, gimple_stmt_iterator *
 		}
 	      else
 		{
-		  vec_oprnd1 = gimple_call_arg (new_stmt, 2*i);
+		  vec_oprnd1 = gimple_call_arg (new_stmt, 2*i + 1);
 		  vec_oprnd0
 		    = vect_get_vec_def_for_stmt_copy (dt[i], vec_oprnd1);
 		  vec_oprnd1
