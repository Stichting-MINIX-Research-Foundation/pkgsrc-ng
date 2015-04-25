$NetBSD$

--- gcc/lto-section-in.c.orig	Wed Nov 25 10:55:54 2009
+++ gcc/lto-section-in.c
@@ -294,7 +294,7 @@ lto_create_simple_input_block (struct lto_file_decl_da
     = (const struct lto_simple_header *) data;
 
   struct lto_input_block* ib_main;
-  int32_t main_offset = sizeof (struct lto_simple_header);
+  int main_offset = sizeof (struct lto_simple_header);
 
   if (!data)
     return NULL;
