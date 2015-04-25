$NetBSD$

--- gcc/gcc.h.orig	Sun Jan  3 17:03:38 2010
+++ gcc/gcc.h
@@ -50,6 +50,7 @@ struct spec_function
   || !strcmp (STR, "iwithprefix") || !strcmp (STR, "iwithprefixbefore") \
   || !strcmp (STR, "iquote") || !strcmp (STR, "isystem") \
   || !strcmp (STR, "isysroot") \
+  || !strcmp (STR, "cxx-isystem") || !strcmp (STR, "-iremap") \
   || !strcmp (STR, "-param") || !strcmp (STR, "specs") \
   || !strcmp (STR, "MF") || !strcmp (STR, "MT") || !strcmp (STR, "MQ") \
   || !strcmp (STR, "fintrinsic-modules-path") \
