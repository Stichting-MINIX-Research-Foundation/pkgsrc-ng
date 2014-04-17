$NetBSD: patch-src_spot_pskrep.cxx,v 1.2 2013/09/13 06:35:55 mef Exp $

Avoid implicit conversions to bool for streams.
Require C++11 for Clang and prefer std version over tr1 when in C++11
mode.

--- src/spot/pskrep.cxx.orig	2013-05-03 14:36:37.000000000 +0000
+++ src/spot/pskrep.cxx
@@ -50,7 +50,11 @@
 #include <algorithm>
 #include <fstream>
 
-#if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)
+#if __cplusplus >= 201103L
+#  define MAP_TYPE std::unordered_map
+#  define HASH_TYPE std::hash
+#  include <unordered_map>
+#elif (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)
 #  define MAP_TYPE std::tr1::unordered_map
 #define HASH_TYPE std::tr1::hash
 #  include <tr1/unordered_map>
