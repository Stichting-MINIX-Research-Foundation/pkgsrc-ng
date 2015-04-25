$NetBSD$

--- libcpp/internal.h.orig	Mon Mar 29 20:07:29 2010
+++ libcpp/internal.h
@@ -179,6 +179,9 @@ struct lexer_state
   /* Nonzero if first token on line is CPP_HASH.  */
   unsigned char in_directive;
 
+  /* Nonzero if we are collecting macro arguments */
+  unsigned char collecting_args;
+
   /* Nonzero if in a directive that will handle padding tokens itself.
      #include needs this to avoid problems with computed include and
      spacing between tokens.  */
