$NetBSD$

--- libmudflap/mf-runtime.c.orig	Sat Jan  9 00:00:42 2010
+++ libmudflap/mf-runtime.c
@@ -31,9 +31,10 @@ see the files COPYING3 and COPYING.RUNTIME respectivel
 
 /* These attempt to coax various unix flavours to declare all our
    needed tidbits in the system headers.  */
-#if !defined(__FreeBSD__) && !defined(__APPLE__)
+#if !defined(__FreeBSD__) && !defined(__APPLE__) && !defined(__NetBSD__)
 #define _POSIX_SOURCE
 #endif /* Some BSDs break <sys/socket.h> if this is defined. */
+#define _NETBSD_SOURCE
 #define _GNU_SOURCE
 #define _XOPEN_SOURCE
 #define _BSD_TYPES
@@ -165,7 +166,7 @@ begin_recursion_protect1 (const char *pf)
 #define LOOKUP_CACHE_SHIFT_DFL 2
 
 struct __mf_cache __mf_lookup_cache [LOOKUP_CACHE_SIZE_MAX];
-uintptr_t __mf_lc_mask = LOOKUP_CACHE_MASK_DFL;
+__mf_uintptr_t __mf_lc_mask = LOOKUP_CACHE_MASK_DFL;
 unsigned char __mf_lc_shift = LOOKUP_CACHE_SHIFT_DFL;
 #define LOOKUP_CACHE_SIZE (__mf_lc_mask + 1)
 
@@ -192,13 +193,19 @@ pthread_mutex_t __mf_biglock =
 /* Use HAVE_PTHREAD_H here instead of LIBMUDFLAPTH, so that even
    the libmudflap.la (no threading support) can diagnose whether
    the application is linked with -lpthread.  See __mf_usage() below.  */
-#if HAVE_PTHREAD_H
-#ifdef _POSIX_THREADS
-#pragma weak pthread_join
+#ifdef LIBMUDFLAPTH
+# if HAVE_PTHREAD_H
+#  ifdef _POSIX_THREADS
+#   include <pthread.h>
+#  else
+#   define pthread_join NULL
+#  endif
+# else
+#  define pthread_join NULL
+# endif
 #else
-#define pthread_join NULL
+# define pthread_join NULL
 #endif
-#endif
 
 
 /* ------------------------------------------------------------------------ */
@@ -1762,7 +1769,7 @@ __mf_describe_object (__mf_object_t *obj)
            "bounds=[%p,%p] size=%lu area=%s check=%ur/%uw liveness=%u%s\n"
            "alloc time=%lu.%06lu pc=%p"
 #ifdef LIBMUDFLAPTH
-           " thread=%u"
+           " thread=%ju"
 #endif
            "\n",
            (obj->deallocated_p ? "dead " : ""),
@@ -1781,7 +1788,7 @@ __mf_describe_object (__mf_object_t *obj)
            obj->alloc_time.tv_sec, obj->alloc_time.tv_usec,
            (void *) obj->alloc_pc
 #ifdef LIBMUDFLAPTH
-           , (unsigned) obj->alloc_thread
+           , (intmax_t)(intptr_t)obj->alloc_thread
 #endif
            );
 
@@ -1798,13 +1805,13 @@ __mf_describe_object (__mf_object_t *obj)
         {
           fprintf (stderr, "dealloc time=%lu.%06lu pc=%p"
 #ifdef LIBMUDFLAPTH
-                   " thread=%u"
+                   " thread=%ju"
 #endif
                    "\n",
                    obj->dealloc_time.tv_sec, obj->dealloc_time.tv_usec,
                    (void *) obj->dealloc_pc
 #ifdef LIBMUDFLAPTH
-                   , (unsigned) obj->dealloc_thread
+                   , (intmax_t)(intptr_t)obj->dealloc_thread
 #endif
                    );
 
@@ -2318,7 +2325,7 @@ __mf_sigusr1_respond ()
 #ifndef NDEBUG
 
 static void
-write_itoa (int fd, unsigned n)
+write_itoa (int fd, intmax_t n)
 {
   enum x { bufsize = sizeof(n)*4 };
   char buf [bufsize];
@@ -2347,7 +2354,7 @@ __assert_fail (const char *msg, const char *file, unsi
   write2("mf");
 #ifdef LIBMUDFLAPTH
   write2("(");
-  write_itoa (2, (unsigned) pthread_self ());
+  write_itoa (2, (intmax_t)(intptr_t)pthread_self ());
   write2(")");
 #endif
   write2(": assertion failure: `");
