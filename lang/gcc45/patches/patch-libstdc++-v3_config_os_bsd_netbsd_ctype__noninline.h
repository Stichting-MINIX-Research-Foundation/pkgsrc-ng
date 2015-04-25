$NetBSD$

--- libstdc++-v3/config/os/bsd/netbsd/ctype_noninline.h.orig	Thu Apr  9 15:00:19 2009
+++ libstdc++-v3/config/os/bsd/netbsd/ctype_noninline.h
@@ -33,11 +33,11 @@
   
 // Information as gleaned from /usr/include/ctype.h
 
-  extern "C" const u_int8_t _C_ctype_[];
+  extern "C" const unsigned short _C_ctype_tab_[];
 
   const ctype_base::mask*
   ctype<char>::classic_table() throw()
-  { return _C_ctype_ + 1; }
+  { return _C_ctype_tab_ + 1; }
 
   ctype<char>::ctype(__c_locale, const mask* __table, bool __del, 
 		     size_t __refs) 
@@ -64,14 +64,14 @@
 
   char
   ctype<char>::do_toupper(char __c) const
-  { return ::toupper((int) __c); }
+  { return ::toupper((int)(unsigned char) __c); }
 
   const char*
   ctype<char>::do_toupper(char* __low, const char* __high) const
   {
     while (__low < __high)
       {
-	*__low = ::toupper((int) *__low);
+	*__low = ::toupper((int)(unsigned char) *__low);
 	++__low;
       }
     return __high;
@@ -79,14 +79,14 @@
 
   char
   ctype<char>::do_tolower(char __c) const
-  { return ::tolower((int) __c); }
+  { return ::tolower((int)(unsigned char) __c); }
 
   const char* 
   ctype<char>::do_tolower(char* __low, const char* __high) const
   {
     while (__low < __high)
       {
-	*__low = ::tolower((int) *__low);
+	*__low = ::tolower((int)(unsigned char) *__low);
 	++__low;
       }
     return __high;
