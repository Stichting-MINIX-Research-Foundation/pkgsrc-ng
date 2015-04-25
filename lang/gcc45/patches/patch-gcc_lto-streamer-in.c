$NetBSD$

--- gcc/lto-streamer-in.c.orig	Wed Jun  2 20:43:42 2010
+++ gcc/lto-streamer-in.c
@@ -1445,9 +1445,9 @@ lto_read_body (struct lto_file_decl_data *file_data, t
 {
   const struct lto_function_header *header;
   struct data_in *data_in;
-  int32_t cfg_offset;
-  int32_t main_offset;
-  int32_t string_offset;
+  int cfg_offset;
+  int main_offset;
+  int string_offset;
   struct lto_input_block ib_cfg;
   struct lto_input_block ib_main;
 
