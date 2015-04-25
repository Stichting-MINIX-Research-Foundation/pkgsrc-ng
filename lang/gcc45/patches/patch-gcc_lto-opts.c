$NetBSD$

--- gcc/lto-opts.c.orig	Wed Nov 25 10:55:54 2009
+++ gcc/lto-opts.c
@@ -351,7 +351,7 @@ lto_read_file_options (struct lto_file_decl_data *file
   size_t len;
   const char *data;
   const struct lto_simple_header *header;
-  int32_t opts_offset;
+  int opts_offset;
   struct lto_input_block ib;
 
   data = lto_get_section_data (file_data, LTO_section_opts, NULL, &len);
