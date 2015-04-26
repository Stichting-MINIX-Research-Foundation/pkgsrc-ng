--- gold/gold.h.orig	Fri Nov  9 08:21:28 2012
+++ gold/gold.h	Fri Jul 18 14:46:06 2014
@@ -66,7 +66,20 @@
 
 // Figure out how to get a hash set and a hash map.
 
-#if defined(HAVE_TR1_UNORDERED_SET) && defined(HAVE_TR1_UNORDERED_MAP) \
+#if defined(HAVE_UNORDERED_SET) && defined(HAVE_UNORDERED_MAP)
+
+#include <unordered_set>
+#include <unordered_map>
+
+// We need a template typedef here.
+
+#define Unordered_set std::unordered_set
+#define Unordered_map std::unordered_map
+#define Unordered_multimap std::unordered_multimap
+
+#define reserve_unordered_map(map, n) ((map)->rehash(n))
+
+#elif defined(HAVE_TR1_UNORDERED_SET) && defined(HAVE_TR1_UNORDERED_MAP) \
     && defined(HAVE_TR1_UNORDERED_MAP_REHASH)
 
 #include <tr1/unordered_set>
