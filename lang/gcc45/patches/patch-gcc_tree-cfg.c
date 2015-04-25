$NetBSD$

--- gcc/tree-cfg.c.orig	Mon Nov 29 19:20:48 2010
+++ gcc/tree-cfg.c
@@ -7092,7 +7092,8 @@ execute_warn_function_return (void)
 	}
       if (location == UNKNOWN_LOCATION)
 	location = cfun->function_end_locus;
-      warning_at (location, 0, "%<noreturn%> function does return");
+      if (warn_missing_noreturn)
+        warning_at (location, 0, "%<noreturn%> function does return");
     }
 
   /* If we see "return;" in some basic block, then we do reach the end
@@ -7294,4 +7295,3 @@ struct gimple_opt_pass pass_warn_unused_result =
     0,					/* todo_flags_finish */
   }
 };
-
