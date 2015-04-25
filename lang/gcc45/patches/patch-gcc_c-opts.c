$NetBSD$

--- gcc/c-opts.c.orig	Fri Apr  2 19:54:46 2010
+++ gcc/c-opts.c
@@ -160,12 +160,14 @@ c_common_missing_argument (const char *opt, size_t cod
       error ("macro name missing after %qs", opt);
       break;
 
+    case OPT_cxx_isystem:
     case OPT_F:
     case OPT_I:
     case OPT_idirafter:
     case OPT_isysroot:
     case OPT_isystem:
     case OPT_iquote:
+    case OPT_iremap:
       error ("missing path after %qs", opt);
       break;
 
@@ -564,6 +566,10 @@ c_common_handle_option (size_t scode, const char *arg,
 	set_std_cxx98 (true);
       break;
 
+    case OPT_cxx_isystem:
+      add_path (xstrdup (arg), SYSTEM, 1, true);
+      break;
+
     case OPT_d:
       handle_OPT_d (arg);
       break;
@@ -877,6 +883,10 @@ c_common_handle_option (size_t scode, const char *arg,
 
     case OPT_isystem:
       add_path (xstrdup (arg), SYSTEM, 0, true);
+      break;
+
+    case OPT_iremap:
+      add_cpp_remap_path (arg);
       break;
 
     case OPT_iwithprefix:
