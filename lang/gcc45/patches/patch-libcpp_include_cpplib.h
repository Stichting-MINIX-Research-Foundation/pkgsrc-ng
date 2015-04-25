$NetBSD$

--- libcpp/include/cpplib.h.orig	Fri Nov 20 08:18:16 2009
+++ libcpp/include/cpplib.h
@@ -674,6 +674,9 @@ extern void cpp_set_lang (cpp_reader *, enum c_lang);
 /* Set the include paths.  */
 extern void cpp_set_include_chains (cpp_reader *, cpp_dir *, cpp_dir *, int);
 
+/* Provide src:dst pair for __FILE__ remapping.  */
+extern void add_cpp_remap_path (const char *);
+
 /* Call these to get pointers to the options, callback, and deps
    structures for a given reader.  These pointers are good until you
    call cpp_finish on that reader.  You can either edit the callbacks
