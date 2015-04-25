$NetBSD$

--- libmudflap/mf-impl.h.orig	Thu Apr  9 15:00:19 2009
+++ libmudflap/mf-impl.h
@@ -273,12 +273,12 @@ extern struct __mf_options __mf_opts;
 #ifdef LIBMUDFLAPTH
 #define VERBOSE_TRACE(...) \
   do { if (UNLIKELY (__mf_opts.verbose_trace)) {  \
-      fprintf (stderr, "mf(%u): ", (unsigned) pthread_self ()); \
+      fprintf (stderr, "mf(%ju): ", (intmax_t)(intptr_t) pthread_self ()); \
       fprintf (stderr, __VA_ARGS__); \
     } } while (0)
 #define TRACE(...) \
   do { if (UNLIKELY (__mf_opts.trace_mf_calls)) { \
-      fprintf (stderr, "mf(%u): ", (unsigned) pthread_self ()); \
+      fprintf (stderr, "mf(%ju): ", (intmax_t)(intptr_t) pthread_self ()); \
       fprintf (stderr, __VA_ARGS__); \
     } } while (0)
 #else
@@ -390,6 +390,29 @@ ret __mfwrap_ ## fname (__VA_ARGS__)
   else if (UNLIKELY (__mf_get_state () == in_malloc))   \
   {                                         \
     return CALL_REAL(fname, __VA_ARGS__);   \
+  }                                         \
+  else                                      \
+  {                                         \
+    TRACE ("%s\n", __PRETTY_FUNCTION__); \
+  }
+
+#define BEGIN_PROTECTV(fname, ...)       \
+  if (UNLIKELY (__mf_starting_p)) \
+  {                                         \
+    CALL_BACKUP(fname, __VA_ARGS__); \
+    return;				\
+  }                                         \
+  else if (UNLIKELY (__mf_get_state () == reentrant))   \
+  {                                         \
+    extern unsigned long __mf_reentrancy;   \
+    __mf_reentrancy ++; \
+    CALL_REAL(fname, __VA_ARGS__);   \
+    return;				\
+  }                                         \
+  else if (UNLIKELY (__mf_get_state () == in_malloc))   \
+  {                                         \
+    CALL_REAL(fname, __VA_ARGS__);   \
+    return;				\
   }                                         \
   else                                      \
   {                                         \
