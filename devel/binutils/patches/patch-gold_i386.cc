$NetBSD$

--- gold/i386.cc.orig	Mon May 19 14:30:54 2014
+++ gold/i386.cc
@@ -2538,6 +2538,10 @@ Target_i386::do_finalize_sections(
   Symbol* sym = this->global_offset_table_;
   if (sym != NULL)
     {
+      // create a plt
+      if (this->plt_ == NULL)
+        this->make_plt_section(symtab, layout);
+
       uint32_t data_size = this->got_plt_->current_data_size();
       symtab->get_sized_symbol<32>(sym)->set_symsize(data_size);
     }
