$NetBSD$

--- libiberty/floatformat.c.orig	Tue Nov 13 00:37:43 2007
+++ libiberty/floatformat.c
@@ -473,7 +473,11 @@ floatformat_to_double (const struct floatformat *fmt,
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
