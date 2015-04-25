$NetBSD$

--- gcc/cp/parser.c.orig	Wed Apr 27 05:20:46 2011
+++ gcc/cp/parser.c
@@ -2333,6 +2333,7 @@ cp_parser_diagnose_invalid_type_name (cp_parser *parse
 				      location_t location)
 {
   tree decl, old_scope;
+  cp_parser_commit_to_tentative_parse (parser);
   /* Try to lookup the identifier.  */
   old_scope = parser->scope;
   parser->scope = scope;
@@ -2423,7 +2424,6 @@ cp_parser_diagnose_invalid_type_name (cp_parser *parse
       else
 	gcc_unreachable ();
     }
-  cp_parser_commit_to_tentative_parse (parser);
 }
 
 /* Check for a common situation where a type-name should be present,
