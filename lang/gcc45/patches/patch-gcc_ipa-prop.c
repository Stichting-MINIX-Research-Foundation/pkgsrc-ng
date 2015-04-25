$NetBSD$

--- gcc/ipa-prop.c.orig	Sat Jul 31 12:11:25 2010
+++ gcc/ipa-prop.c
@@ -2134,9 +2134,9 @@ ipa_prop_read_section (struct lto_file_decl_data *file
 {
   const struct lto_function_header *header =
     (const struct lto_function_header *) data;
-  const int32_t cfg_offset = sizeof (struct lto_function_header);
-  const int32_t main_offset = cfg_offset + header->cfg_size;
-  const int32_t string_offset = main_offset + header->main_size;
+  const int cfg_offset = sizeof (struct lto_function_header);
+  const int main_offset = cfg_offset + header->cfg_size;
+  const int string_offset = main_offset + header->main_size;
   struct data_in *data_in;
   struct lto_input_block ib_main;
   unsigned int i;
