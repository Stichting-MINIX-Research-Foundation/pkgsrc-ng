$NetBSD$

--- libcpp/lex.c.orig	Tue Apr 26 10:04:18 2011
+++ libcpp/lex.c
@@ -1092,6 +1092,8 @@ save_comment (cpp_reader *pfile, cpp_token *token, con
 {
   unsigned char *buffer;
   unsigned int len, clen;
+  int convert_to_c = (pfile->state.in_directive || pfile->state.collecting_args)
+    && type == '/';
 
   len = pfile->buffer->cur - from + 1; /* + 1 for the initial '/'.  */
 
@@ -1106,7 +1108,7 @@ save_comment (cpp_reader *pfile, cpp_token *token, con
 
      Note that the only time we encounter a directive here is
      when we are saving comments in a "#define".  */
-  clen = (pfile->state.in_directive && type == '/') ? len + 2 : len;
+  clen = convert_to_c ? len + 2 : len;
 
   buffer = _cpp_unaligned_alloc (pfile, clen);
 
@@ -1118,7 +1120,7 @@ save_comment (cpp_reader *pfile, cpp_token *token, con
   memcpy (buffer + 1, from, len - 1);
 
   /* Finish conversion to a C comment, if necessary.  */
-  if (pfile->state.in_directive && type == '/')
+  if (convert_to_c)
     {
       buffer[1] = '*';
       buffer[clen - 2] = '*';
