$NetBSD$

--- gcc/gengtype-lex.c.orig	Thu Apr 28 14:32:36 2011
+++ gcc/gengtype-lex.c
@@ -933,7 +933,7 @@ int yy_flex_debug = 0;
 #define YY_MORE_ADJ 0
 #define YY_RESTORE_YY_MORE_OFFSET
 char *yytext;
-#line 1 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 1 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 /* -*- indented-text -*- */
 /* Process source files and output type information.
    Copyright (C) 2002, 2003, 2004, 2005, 2007, 2008, 2009
@@ -955,7 +955,7 @@ You should have received a copy of the GNU General Pub
 along with GCC; see the file COPYING3.  If not see
 <http://www.gnu.org/licenses/>.  */
 #define YY_NO_INPUT 1
-#line 25 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 25 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 #include "bconfig.h"
 #include "system.h"
 
@@ -1165,7 +1165,7 @@ YY_DECL
 	register char *yy_cp, *yy_bp;
 	register int yy_act;
     
-#line 59 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 59 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 
   /* Do this on entry to yylex():  */
   *yylval = 0;
@@ -1262,7 +1262,7 @@ case 1:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 70 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 70 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   BEGIN(in_struct);
   return TYPEDEF;
@@ -1274,7 +1274,7 @@ case 2:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 74 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 74 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   BEGIN(in_struct);
   return STRUCT;
@@ -1286,7 +1286,7 @@ case 3:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 78 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 78 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   BEGIN(in_struct);
   return UNION;
@@ -1298,7 +1298,7 @@ case 4:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 82 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 82 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   BEGIN(in_struct);
   return EXTERN;
@@ -1310,7 +1310,7 @@ case 5:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 86 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 86 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   BEGIN(in_struct);
   return STATIC;
@@ -1322,7 +1322,7 @@ case 6:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 91 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 91 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   BEGIN(in_struct);
   return DEFVEC_OP;
@@ -1334,7 +1334,7 @@ case 7:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 95 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 95 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   BEGIN(in_struct);
   return DEFVEC_I;
@@ -1346,7 +1346,7 @@ case 8:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 99 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 99 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   BEGIN(in_struct);
   return DEFVEC_ALLOC;
@@ -1356,19 +1356,19 @@ YY_RULE_SETUP
 
 case 9:
 YY_RULE_SETUP
-#line 107 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 107 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { BEGIN(in_struct_comment); }
 	YY_BREAK
 case 10:
 /* rule 10 can match eol */
 YY_RULE_SETUP
-#line 109 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 109 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { update_lineno (yytext, yyleng); }
 	YY_BREAK
 case 11:
 /* rule 11 can match eol */
 YY_RULE_SETUP
-#line 110 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 110 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { lexer_line.line++; }
 	YY_BREAK
 case 12:
@@ -1377,7 +1377,7 @@ case 12:
 (yy_c_buf_p) = yy_cp = yy_bp + 5;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 112 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 112 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 /* don't care */
 	YY_BREAK
 case 13:
@@ -1386,7 +1386,7 @@ case 13:
 (yy_c_buf_p) = yy_cp = yy_bp + 3;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 113 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 113 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return GTY_TOKEN; }
 	YY_BREAK
 case 14:
@@ -1395,7 +1395,7 @@ case 14:
 (yy_c_buf_p) = yy_cp = yy_bp + 3;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 114 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 114 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return VEC_TOKEN; }
 	YY_BREAK
 case 15:
@@ -1404,7 +1404,7 @@ case 15:
 (yy_c_buf_p) = yy_cp = yy_bp + 5;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 115 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 115 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return UNION; }
 	YY_BREAK
 case 16:
@@ -1413,7 +1413,7 @@ case 16:
 (yy_c_buf_p) = yy_cp = yy_bp + 6;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 116 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 116 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return STRUCT; }
 	YY_BREAK
 case 17:
@@ -1422,7 +1422,7 @@ case 17:
 (yy_c_buf_p) = yy_cp = yy_bp + 4;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 117 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 117 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return ENUM; }
 	YY_BREAK
 case 18:
@@ -1431,7 +1431,7 @@ case 18:
 (yy_c_buf_p) = yy_cp = yy_bp + 9;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 118 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 118 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return PTR_ALIAS; }
 	YY_BREAK
 case 19:
@@ -1440,12 +1440,12 @@ case 19:
 (yy_c_buf_p) = yy_cp = yy_bp + 10;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 119 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 119 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return NESTED_PTR; }
 	YY_BREAK
 case 20:
 YY_RULE_SETUP
-#line 120 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 120 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return NUM; }
 	YY_BREAK
 case 21:
@@ -1454,7 +1454,7 @@ case 21:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 121 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 121 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   *yylval = XDUPVAR (const char, yytext, yyleng, yyleng+1);
   return PARAM_IS;
@@ -1465,11 +1465,11 @@ case 22:
 *yy_cp = (yy_hold_char); /* undo effects of setting up yytext */
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
-#line 127 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 127 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 case 23:
 /* rule 23 can match eol */
 YY_RULE_SETUP
-#line 127 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 127 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   size_t len;
 
@@ -1487,7 +1487,7 @@ case 24:
 (yy_c_buf_p) = yy_cp -= 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 139 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 139 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   *yylval = XDUPVAR (const char, yytext, yyleng, yyleng+1);
   return ID;
@@ -1496,7 +1496,7 @@ YY_RULE_SETUP
 case 25:
 /* rule 25 can match eol */
 YY_RULE_SETUP
-#line 144 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 144 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   *yylval = XDUPVAR (const char, yytext+1, yyleng-2, yyleng-1);
   return STRING;
@@ -1506,7 +1506,7 @@ YY_RULE_SETUP
 case 26:
 /* rule 26 can match eol */
 YY_RULE_SETUP
-#line 149 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 149 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   *yylval = XDUPVAR (const char, yytext+1, yyleng-2, yyleng-1);
   return ARRAY;
@@ -1515,7 +1515,7 @@ YY_RULE_SETUP
 case 27:
 /* rule 27 can match eol */
 YY_RULE_SETUP
-#line 153 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 153 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   *yylval = XDUPVAR (const char, yytext+1, yyleng-2, yyleng);
   return CHAR;
@@ -1523,24 +1523,24 @@ YY_RULE_SETUP
 	YY_BREAK
 case 28:
 YY_RULE_SETUP
-#line 158 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 158 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return ELLIPSIS; }
 	YY_BREAK
 case 29:
 YY_RULE_SETUP
-#line 159 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 159 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { return yytext[0]; }
 	YY_BREAK
 /* ignore pp-directives */
 case 30:
 /* rule 30 can match eol */
 YY_RULE_SETUP
-#line 162 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 162 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {lexer_line.line++;}
 	YY_BREAK
 case 31:
 YY_RULE_SETUP
-#line 164 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 164 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   error_at_line (&lexer_line, "unexpected character `%s'", yytext);
 }
@@ -1548,30 +1548,30 @@ YY_RULE_SETUP
 
 case 32:
 YY_RULE_SETUP
-#line 169 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 169 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { BEGIN(in_comment); }
 	YY_BREAK
 case 33:
 /* rule 33 can match eol */
 YY_RULE_SETUP
-#line 170 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 170 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { lexer_line.line++; }
 	YY_BREAK
 case 34:
-#line 172 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 172 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 case 35:
 /* rule 35 can match eol */
-#line 173 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 173 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 case 36:
 /* rule 36 can match eol */
 YY_RULE_SETUP
-#line 173 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 173 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 /* do nothing */
 	YY_BREAK
 case 37:
 /* rule 37 can match eol */
 YY_RULE_SETUP
-#line 174 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 174 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { update_lineno (yytext, yyleng); }
 	YY_BREAK
 case 38:
@@ -1580,21 +1580,21 @@ case 38:
 (yy_c_buf_p) = yy_cp = yy_bp + 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 175 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 175 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 /* do nothing */
 	YY_BREAK
 
 case 39:
 /* rule 39 can match eol */
 YY_RULE_SETUP
-#line 178 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 178 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { lexer_line.line++; }
 	YY_BREAK
 case 40:
-#line 180 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 180 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 case 41:
 YY_RULE_SETUP
-#line 180 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 180 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 /* do nothing */
 	YY_BREAK
 case 42:
@@ -1603,25 +1603,25 @@ case 42:
 (yy_c_buf_p) = yy_cp = yy_bp + 1;
 YY_DO_BEFORE_ACTION; /* set up yytext again */
 YY_RULE_SETUP
-#line 181 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 181 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 /* do nothing */
 	YY_BREAK
 
 case 43:
 YY_RULE_SETUP
-#line 183 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 183 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { BEGIN(INITIAL); } 
 	YY_BREAK
 case 44:
 YY_RULE_SETUP
-#line 184 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 184 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 { BEGIN(in_struct); }
 	YY_BREAK
 case 45:
-#line 187 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 187 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 case 46:
 YY_RULE_SETUP
-#line 187 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 187 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 {
   error_at_line (&lexer_line, 
 		 "unterminated comment or string; unexpected EOF");
@@ -1630,12 +1630,12 @@ YY_RULE_SETUP
 case 47:
 /* rule 47 can match eol */
 YY_RULE_SETUP
-#line 192 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 192 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 /* do nothing */
 	YY_BREAK
 case 48:
 YY_RULE_SETUP
-#line 194 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 194 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 YY_FATAL_ERROR( "flex scanner jammed" );
 	YY_BREAK
 #line 1642 "gengtype-lex.c"
@@ -2602,7 +2602,7 @@ void yyfree (void * ptr )
 
 #define YYTABLES_NAME "yytables"
 
-#line 194 "/space/rguenther/gcc-4.5.3/gcc-4.5.3/gcc/gengtype-lex.l"
+#line 194 "/space/rguenther/gcc-4.5.4/gcc-4.5.4/gcc/gengtype-lex.l"
 
 
 
