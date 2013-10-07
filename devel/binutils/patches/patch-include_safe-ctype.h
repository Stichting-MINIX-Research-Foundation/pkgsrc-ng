--- include/safe-ctype.h.orig	Mon Jul  7 17:09:31 2008
+++ include/safe-ctype.h	Fri Jul 18 14:46:06 2014
@@ -119,6 +119,7 @@ extern const unsigned char  _sch_tolower[256];
    including another system header (for instance gnulib's stdint.h).
    So we include ctype.h here and then immediately redefine its macros.  */
 
+#if !defined(__minix) || !defined(__clang__)
 #include <ctype.h>
 #undef isalpha
 #define isalpha(c) do_not_use_isalpha_with_safe_ctype
@@ -145,6 +146,34 @@ extern const unsigned char  _sch_tolower[256];
 #undef toupper
 #define toupper(c) do_not_use_toupper_with_safe_ctype
 #undef tolower
-#define tolower(c) do_not_use_tolower_with_safe_ctype
+#else
+#include <ctype.h>
+#undef isalpha
+#define isalpha(c) ISALPHA(c)
+#undef isalnum
+#define isalnum(c) ISALNUM(c)
+#undef iscntrl
+#define iscntrl(c) ISCNTRL(c)
+#undef isdigit
+#define isdigit(c) ISDIGIT(c)
+#undef isgraph
+#define isgraph(c) ISGRAPH(c)
+#undef islower
+#define islower(c) ISLOWER(c)
+#undef isprint
+#define isprint(c) ISPRINT(c)
+#undef ispunct
+#define ispunct(c) ISPUNCT(c)
+#undef isspace
+#define isspace(c) ISSPACE(c)
+#undef isupper
+#define isupper(c) ISUPPER(c)
+#undef isxdigit
+#define isxdigit(c) ISXDIGIT(c)
+#undef toupper
+#define toupper(c) TOUPPER(c)
+#undef tolower
+#define tolower(c) TOLOWER(c)
+#endif /* !defined(__minix) || !defined(__clang__) */
 
 #endif /* SAFE_CTYPE_H */
