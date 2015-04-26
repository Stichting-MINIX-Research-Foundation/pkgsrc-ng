--- gold/stringpool.cc.orig	Wed Aug 25 08:36:54 2010
+++ gold/stringpool.cc	Fri Jul 18 14:46:06 2014
@@ -72,7 +72,10 @@ Stringpool_template<Stringpool_char>::reserve(unsigned
 {
   this->key_to_offset_.reserve(n);
 
-#if defined(HAVE_TR1_UNORDERED_MAP)
+#if defined(HAVE_UNORDERED_MAP)
+  this->string_set_.rehash(this->string_set_.size() + n);
+  return;
+#elif defined(HAVE_TR1_UNORDERED_MAP)
   // rehash() implementation is broken in gcc 4.0.3's stl
   //this->string_set_.rehash(this->string_set_.size() + n);
   //return;
@@ -499,7 +502,7 @@ template<typename Stringpool_char>
 void
 Stringpool_template<Stringpool_char>::print_stats(const char* name) const
 {
-#if defined(HAVE_TR1_UNORDERED_MAP) || defined(HAVE_EXT_HASH_MAP)
+#if  defined(HAVE_UNORDERED_MAP) || defined(HAVE_TR1_UNORDERED_MAP) || defined(HAVE_EXT_HASH_MAP)
   fprintf(stderr, _("%s: %s entries: %zu; buckets: %zu\n"),
 	  program_name, name, this->string_set_.size(),
 	  this->string_set_.bucket_count());
