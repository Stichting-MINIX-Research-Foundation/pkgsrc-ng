$NetBSD$

--- libobjc/archive.c.orig	Thu Apr  9 15:00:19 2009
+++ libobjc/archive.c
@@ -365,7 +365,7 @@ __objc_write_extension (struct objc_typed_stream *stre
     }
 }
 
-inline int
+int
 __objc_write_object (struct objc_typed_stream *stream, id object)
 {
   unsigned char buf = '\0';
@@ -431,7 +431,7 @@ objc_write_object (struct objc_typed_stream *stream, i
     }
 }
 
-inline int
+int
 __objc_write_class (struct objc_typed_stream *stream, struct objc_class *class)
 {
   __objc_write_extension (stream, _BX_CLASS);
@@ -460,7 +460,7 @@ objc_write_class (struct objc_typed_stream *stream,
 }
 
 
-inline int 
+int 
 __objc_write_selector (struct objc_typed_stream *stream, SEL selector)
 {
   const char *sel_name;
@@ -503,7 +503,7 @@ objc_write_selector (struct objc_typed_stream *stream,
 ** Read operations 
 */
 
-inline int
+int
 objc_read_char (struct objc_typed_stream *stream, char *val)
 {
   unsigned char buf;
@@ -530,7 +530,7 @@ objc_read_char (struct objc_typed_stream *stream, char
 }
 
 
-inline int
+int
 objc_read_unsigned_char (struct objc_typed_stream *stream, unsigned char *val)
 {
   unsigned char buf;
@@ -551,7 +551,7 @@ objc_read_unsigned_char (struct objc_typed_stream *str
   return len;
 }
 
-inline int
+int
 objc_read_short (struct objc_typed_stream *stream, short *value)
 {
   unsigned char buf[sizeof (short) + 1];
@@ -579,7 +579,7 @@ objc_read_short (struct objc_typed_stream *stream, sho
   return len;
 }
 
-inline int
+int
 objc_read_unsigned_short (struct objc_typed_stream *stream,
 			  unsigned short *value)
 {
@@ -607,7 +607,7 @@ objc_read_unsigned_short (struct objc_typed_stream *st
 }
 
 
-inline int
+int
 objc_read_int (struct objc_typed_stream *stream, int *value)
 {
   unsigned char buf[sizeof (int) + 1];
@@ -634,7 +634,7 @@ objc_read_int (struct objc_typed_stream *stream, int *
   return len;
 }
 
-inline int
+int
 objc_read_long (struct objc_typed_stream *stream, long *value)
 {
   unsigned char buf[sizeof (long) + 1];
@@ -661,7 +661,7 @@ objc_read_long (struct objc_typed_stream *stream, long
   return len;
 }
 
-inline int
+int
 __objc_read_nbyte_uint (struct objc_typed_stream *stream,
 			unsigned int nbytes, unsigned int *val)
 {
@@ -680,7 +680,7 @@ __objc_read_nbyte_uint (struct objc_typed_stream *stre
 }
   
 
-inline int
+int
 objc_read_unsigned_int (struct objc_typed_stream *stream,
 			unsigned int *value)
 {
@@ -717,7 +717,7 @@ __objc_read_nbyte_ulong (struct objc_typed_stream *str
 }
   
 
-inline int
+int
 objc_read_unsigned_long (struct objc_typed_stream *stream,
 			 unsigned long *value)
 {
@@ -735,7 +735,7 @@ objc_read_unsigned_long (struct objc_typed_stream *str
   return len;
 }
 
-inline int
+int
 objc_read_string (struct objc_typed_stream *stream,
 		  char **string)
 {
