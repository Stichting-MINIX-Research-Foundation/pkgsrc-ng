$NetBSD$

--- libgomp/fortran.c.orig	Thu Apr  9 15:00:19 2009
+++ libgomp/fortran.c
@@ -1,4 +1,4 @@
-/* Copyright (C) 2005, 2007, 2008, 2009 Free Software Foundation, Inc.
+/* Copyright (C) 2005, 2007, 2008, 2009, 2011 Free Software Foundation, Inc.
    Contributed by Jakub Jelinek <jakub@redhat.com>.
 
    This file is part of the GNU OpenMP Library (libgomp).
@@ -27,6 +27,7 @@
 #include "libgomp.h"
 #include "libgomp_f.h"
 #include <stdlib.h>
+#include <limits.h>
 
 #ifdef HAVE_ATTRIBUTE_ALIAS
 /* Use internal aliases if possible.  */
@@ -244,6 +245,8 @@ omp_lock_symver (omp_unset_nest_lock_)
 omp_lock_symver (omp_test_nest_lock_)
 #endif
 
+#define TO_INT(x) ((x) > INT_MIN ? (x) < INT_MAX ? (x) : INT_MAX : INT_MIN)
+
 void
 omp_set_dynamic_ (const int32_t *set)
 {
@@ -253,7 +256,7 @@ omp_set_dynamic_ (const int32_t *set)
 void
 omp_set_dynamic_8_ (const int64_t *set)
 {
-  omp_set_dynamic (*set);
+  omp_set_dynamic (!!*set);
 }
 
 void
@@ -265,7 +268,7 @@ omp_set_nested_ (const int32_t *set)
 void
 omp_set_nested_8_ (const int64_t *set)
 {
-  omp_set_nested (*set);
+  omp_set_nested (!!*set);
 }
 
 void
@@ -277,7 +280,7 @@ omp_set_num_threads_ (const int32_t *set)
 void
 omp_set_num_threads_8_ (const int64_t *set)
 {
-  omp_set_num_threads (*set);
+  omp_set_num_threads (TO_INT (*set));
 }
 
 int32_t
@@ -343,7 +346,7 @@ omp_set_schedule_ (const int32_t *kind, const int32_t 
 void
 omp_set_schedule_8_ (const int32_t *kind, const int64_t *modifier)
 {
-  omp_set_schedule (*kind, *modifier);
+  omp_set_schedule (*kind, TO_INT (*modifier));
 }
 
 void
@@ -381,7 +384,7 @@ omp_set_max_active_levels_ (const int32_t *levels)
 void
 omp_set_max_active_levels_8_ (const int64_t *levels)
 {
-  omp_set_max_active_levels (*levels);
+  omp_set_max_active_levels (TO_INT (*levels));
 }
 
 int32_t
@@ -405,7 +408,7 @@ omp_get_ancestor_thread_num_ (const int32_t *level)
 int32_t
 omp_get_ancestor_thread_num_8_ (const int64_t *level)
 {
-  return omp_get_ancestor_thread_num (*level);
+  return omp_get_ancestor_thread_num (TO_INT (*level));
 }
 
 int32_t
@@ -417,7 +420,7 @@ omp_get_team_size_ (const int32_t *level)
 int32_t
 omp_get_team_size_8_ (const int64_t *level)
 {
-  return omp_get_team_size (*level);
+  return omp_get_team_size (TO_INT (*level));
 }
 
 int32_t
