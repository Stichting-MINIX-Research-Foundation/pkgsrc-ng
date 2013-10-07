$NetBSD$

--- ld/ldlex.l.orig	Tue Sep  4 14:14:15 2012
+++ ld/ldlex.l
@@ -60,10 +60,6 @@ const char *lex_string = NULL;
 #undef YY_INPUT
 #define YY_INPUT(buf,result,max_size) result = yy_input (buf, max_size)
 
-#ifndef YY_NO_UNPUT
-#define YY_NO_UNPUT
-#endif
-
 #define MAX_INCLUDE_DEPTH 10
 static YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
 static const char *file_name_stack[MAX_INCLUDE_DEPTH];
@@ -93,6 +89,8 @@ static void lex_warn_invalid (char *where, char *what)
 int yywrap (void) { return 1; }
 #endif
 %}
+
+%option nounput
 
 %a 4000
 %o 5000
