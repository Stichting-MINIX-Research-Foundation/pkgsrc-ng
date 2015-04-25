$NetBSD$

--- gcc/testsuite/g++.dg/gcov/gcov-2.C.orig	Thu Jul 16 22:29:52 2009
+++ gcc/testsuite/g++.dg/gcov/gcov-2.C
@@ -20,7 +20,7 @@ class C { (private)
 
 void foo()
 {
-  C c;					/* count(2) */
+  C c;					/* count(1) */
   c.seti (1);				/* count(1) */
 }
 
