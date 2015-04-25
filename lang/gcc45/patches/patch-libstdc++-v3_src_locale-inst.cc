$NetBSD$

--- libstdc++-v3/src/locale-inst.cc.orig	Thu Apr  9 15:00:19 2009
+++ libstdc++-v3/src/locale-inst.cc
@@ -175,11 +175,11 @@ _GLIBCXX_END_LDBL_NAMESPACE
   template class messages_byname<C>;
   
   // ctype
-  inline template class __ctype_abstract_base<C>;
+  template class __ctype_abstract_base<C>;
   template class ctype_byname<C>;
   
   // codecvt
-  inline template class __codecvt_abstract_base<C, char, mbstate_t>;
+  template class __codecvt_abstract_base<C, char, mbstate_t>;
   template class codecvt_byname<C, char, mbstate_t>;
 
   // collate
