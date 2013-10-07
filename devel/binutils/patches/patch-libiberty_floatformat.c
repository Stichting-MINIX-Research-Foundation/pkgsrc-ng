$NetBSD$

--- libiberty/floatformat.c.orig	Mon Jan  3 21:05:58 2011
+++ libiberty/floatformat.c
@@ -489,7 +489,11 @@ floatformat_to_double (const struct floatformat *fmt,
       if (nan)
 	dto = NAN;
       else
+#ifdef __vax__
+	dto = HUGE_VAL;
+#else
 	dto = INFINITY;
+#endif
 
       if (get_field (ufrom, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1))
 	dto = -dto;
