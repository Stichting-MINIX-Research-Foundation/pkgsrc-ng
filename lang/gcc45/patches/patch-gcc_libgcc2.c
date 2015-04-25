$NetBSD$

--- gcc/libgcc2.c.orig	Thu Sep 24 19:02:44 2009
+++ gcc/libgcc2.c
@@ -1802,15 +1802,19 @@ NAME (TYPE x, int m)
 #define isfinite(x)	__builtin_expect (!isnan((x) - (x)), 1)
 #define isinf(x)	__builtin_expect (!isnan(x) & !isfinite(x), 0)
 
+#if TARGET_FLOAT_FORMAT == IEEE_FLOAT_FORMAT
 #define INFINITY	CONCAT2(__builtin_huge_val, CEXT) ()
+#endif
 #define I		1i
 
 /* Helpers to make the following code slightly less gross.  */
 #define COPYSIGN	CONCAT2(__builtin_copysign, CEXT)
 #define FABS		CONCAT2(__builtin_fabs, CEXT)
 
+#ifdef INFINITY
 /* Verify that MTYPE matches up with CEXT.  */
 extern void *compile_type_assert[sizeof(INFINITY) == sizeof(MTYPE) ? 1 : -1];
+#endif
 
 /* Ensure that we've lost any extra precision.  */
 #if NOTRUNC
@@ -1841,6 +1845,7 @@ CONCAT3(__mul,MODE,3) (MTYPE a, MTYPE b, MTYPE c, MTYP
   x = ac - bd;
   y = ad + bc;
 
+#ifdef INFINITY
   if (isnan (x) && isnan (y))
     {
       /* Recover infinities that computed as NaN + iNaN.  */
@@ -1882,6 +1887,7 @@ CONCAT3(__mul,MODE,3) (MTYPE a, MTYPE b, MTYPE c, MTYP
 	  y = INFINITY * (a * d + b * c);
 	}
     }
+#endif
 
   __real__ res = x;
   __imag__ res = y;
@@ -1917,6 +1923,7 @@ CONCAT3(__div,MODE,3) (MTYPE a, MTYPE b, MTYPE c, MTYP
       y = (b - (a * ratio)) / denom;
     }
 
+#ifdef INFINITY
   /* Recover infinities and zeros that computed as NaN+iNaN; the only cases
      are nonzero/zero, infinite/finite, and finite/infinite.  */
   if (isnan (x) && isnan (y))
@@ -1941,6 +1948,7 @@ CONCAT3(__div,MODE,3) (MTYPE a, MTYPE b, MTYPE c, MTYP
 	  y = 0.0 * (b * c - a * d);
 	}
     }
+#endif
 
   __real__ res = x;
   __imag__ res = y;
@@ -1948,6 +1956,7 @@ CONCAT3(__div,MODE,3) (MTYPE a, MTYPE b, MTYPE c, MTYP
 }
 #endif /* complex divide */
 
+#undef INFINITY
 #endif /* all complex float routines */
 
 /* From here on down, the routines use normal data types.  */
