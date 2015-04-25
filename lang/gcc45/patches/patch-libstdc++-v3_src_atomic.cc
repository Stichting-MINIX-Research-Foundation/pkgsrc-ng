$NetBSD$

--- libstdc++-v3/src/atomic.cc.orig	Tue Dec 22 08:23:08 2009
+++ libstdc++-v3/src/atomic.cc
@@ -80,7 +80,7 @@ namespace std
     atomic_flag_test_and_set_explicit(__atomic_flag_base* __a,
 				      memory_order __m) throw()
     {
-      atomic_flag* d = static_cast<volatile atomic_flag*>(__a);
+      atomic_flag* d = static_cast<atomic_flag*>(__a);
       return d->test_and_set(__m);
     }
 
@@ -88,7 +88,7 @@ namespace std
     atomic_flag_clear_explicit(__atomic_flag_base* __a, 
 			       memory_order __m) throw()
     {
-      atomic_flag* d = static_cast<volatile atomic_flag*>(__a);
+      atomic_flag* d = static_cast<atomic_flag*>(__a);
       return d->clear(__m);
     }
 
