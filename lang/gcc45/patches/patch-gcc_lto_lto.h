$NetBSD$

--- gcc/lto/lto.h.orig	Thu Jun 24 21:06:37 2010
+++ gcc/lto/lto.h
@@ -58,6 +58,6 @@ struct lto_section_slot
   size_t len;
 };
 
-int64_t lto_parse_hex (const char *p);
+extern HOST_WIDEST_INT lto_parse_hex (const char *p);
 
 #endif /* LTO_H */
