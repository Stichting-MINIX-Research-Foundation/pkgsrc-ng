$NetBSD$

--- libobjc/encoding.c.orig	Sat Nov 28 20:31:39 2009
+++ libobjc/encoding.c
@@ -544,7 +544,7 @@ objc_promoted_size (const char *type)
   occurring in method prototype encodings.
 */
 
-inline const char *
+const char *
 objc_skip_type_qualifiers (const char *type)
 {
   while (*type == _C_CONST
@@ -682,7 +682,7 @@ objc_skip_typespec (const char *type)
   Skip an offset as part of a method encoding.  This is prepended by a
   '+' if the argument is passed in registers.
 */
-inline const char *
+const char *
 objc_skip_offset (const char *type)
 {
   if (*type == '+')
