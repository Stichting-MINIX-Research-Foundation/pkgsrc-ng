$NetBSD$

--- gcc/lto/lto.c.orig	Mon Jun 14 10:38:18 2010
+++ gcc/lto/lto.c
@@ -157,7 +157,7 @@ lto_read_in_decl_state (struct data_in *data_in, const
   uint32_t ix;
   tree decl;
   uint32_t i, j;
-  
+
   ix = *data++;
   decl = lto_streamer_cache_get (data_in->reader_cache, (int) ix);
   if (TREE_CODE (decl) != FUNCTION_DECL)
@@ -200,9 +200,9 @@ lto_read_decls (struct lto_file_decl_data *decl_data, 
 		VEC(ld_plugin_symbol_resolution_t,heap) *resolutions)
 {
   const struct lto_decl_header *header = (const struct lto_decl_header *) data;
-  const int32_t decl_offset = sizeof (struct lto_decl_header);
-  const int32_t main_offset = decl_offset + header->decl_state_size;
-  const int32_t string_offset = main_offset + header->main_size;
+  const int decl_offset = sizeof (struct lto_decl_header);
+  const int main_offset = decl_offset + header->decl_state_size;
+  const int string_offset = main_offset + header->main_size;
   struct lto_input_block ib_main;
   struct data_in *data_in;
   unsigned int i;
@@ -250,17 +250,20 @@ lto_read_decls (struct lto_file_decl_data *decl_data, 
 
   if (data_ptr != data_end)
     internal_error ("bytecode stream: garbage at the end of symbols section");
-  
+
   /* Set the current decl state to be the global state. */
   decl_data->current_decl_state = decl_data->global_decl_state;
 
   lto_data_in_delete (data_in);
 }
 
-/* strtoll is not portable. */
-int64_t
-lto_parse_hex (const char *p) {
-  uint64_t ret = 0;
+/* Custom version of strtoll, which is not portable.  */
+
+HOST_WIDEST_INT
+lto_parse_hex (const char *p)
+{
+  HOST_WIDEST_INT ret = 0;
+
   for (; *p != '\0'; ++p)
     {
       char c = *p;
@@ -276,6 +279,7 @@ lto_parse_hex (const char *p) {
         internal_error ("could not parse hex number");
       ret |= part;
     }
+
   return ret;
 }
 
@@ -311,7 +315,7 @@ lto_resolution_read (FILE *resolution, lto_file *file)
     {
       int t;
       char offset_p[17];
-      int64_t offset;
+      HOST_WIDEST_INT offset;
       t = fscanf (resolution, "@0x%16s", offset_p);
       if (t != 1)
         internal_error ("could not parse file offset");
