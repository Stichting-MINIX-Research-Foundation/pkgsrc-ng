$NetBSD$

--- gcc/hwint.h.orig	Wed Nov 25 10:55:54 2009
+++ gcc/hwint.h
@@ -78,6 +78,7 @@ extern char sizeof_long_long_must_be_8[sizeof(long lon
 #if HOST_BITS_PER_WIDE_INT == HOST_BITS_PER_LONG
 # define HOST_WIDE_INT_PRINT HOST_LONG_FORMAT
 # define HOST_WIDE_INT_PRINT_C "L"
+# define HOST_WIDE_INT_CONSTANT(x) x ## L
   /* 'long' might be 32 or 64 bits, and the number of leading zeroes
      must be tweaked accordingly.  */
 # if HOST_BITS_PER_WIDE_INT == 64
@@ -90,6 +91,7 @@ extern char sizeof_long_long_must_be_8[sizeof(long lon
 #else
 # define HOST_WIDE_INT_PRINT HOST_LONG_LONG_FORMAT
 # define HOST_WIDE_INT_PRINT_C "LL"
+# define HOST_WIDE_INT_CONSTANT(x) x ## LL
   /* We can assume that 'long long' is at least 64 bits.  */
 # define HOST_WIDE_INT_PRINT_DOUBLE_HEX \
     "0x%" HOST_LONG_LONG_FORMAT "x%016" HOST_LONG_LONG_FORMAT "x"
