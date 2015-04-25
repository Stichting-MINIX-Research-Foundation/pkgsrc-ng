$NetBSD$

--- libstdc++-v3/config/os/bsd/netbsd/ctype_base.h.orig	Thu Apr  9 15:00:19 2009
+++ libstdc++-v3/config/os/bsd/netbsd/ctype_base.h
@@ -30,7 +30,7 @@
 // Full details can be found from the CVS files at:
 //   anoncvs@anoncvs.netbsd.org:/cvsroot/basesrc/include/ctype.h
 // See www.netbsd.org for details of access.
-  
+
 _GLIBCXX_BEGIN_NAMESPACE(std)
 
   /// @brief  Base class for ctype.
@@ -41,18 +41,18 @@ _GLIBCXX_BEGIN_NAMESPACE(std)
 
     // NB: Offsets into ctype<char>::_M_table force a particular size
     // on the mask type. Because of this, we don't use an enum.
-    typedef unsigned char      	mask;
-    static const mask upper    	= _U;
-    static const mask lower 	= _L;
-    static const mask alpha 	= _U | _L;
-    static const mask digit 	= _N;
-    static const mask xdigit 	= _N | _X;
-    static const mask space 	= _S;
-    static const mask print 	= _P | _U | _L | _N | _B;
-    static const mask graph 	= _P | _U | _L | _N;
-    static const mask cntrl 	= _C;
-    static const mask punct 	= _P;
-    static const mask alnum 	= _U | _L | _N;
+    typedef unsigned short     	mask;
+    static const mask upper    	= _CTYPE_U;
+    static const mask lower 	= _CTYPE_L;
+    static const mask alpha 	= _CTYPE_A;
+    static const mask digit 	= _CTYPE_D;
+    static const mask xdigit 	= _CTYPE_X;
+    static const mask space 	= _CTYPE_S;
+    static const mask print 	= _CTYPE_R;
+    static const mask graph 	= _CTYPE_G;
+    static const mask cntrl 	= _CTYPE_C;
+    static const mask punct 	= _CTYPE_P;
+    static const mask alnum 	= _CTYPE_A | _CTYPE_D;
   };
 
 _GLIBCXX_END_NAMESPACE
