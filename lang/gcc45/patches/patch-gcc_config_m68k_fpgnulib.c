$NetBSD$

--- gcc/config/m68k/fpgnulib.c.orig	Thu Jan 18 19:49:59 2007
+++ gcc/config/m68k/fpgnulib.c
@@ -549,6 +549,7 @@ __negxf2 (long double x1)
   return - (double) x1;
 }
 
+long __cmpdf2 (double, double);
 long
 __cmpxf2 (long double x1, long double x2)
 {
