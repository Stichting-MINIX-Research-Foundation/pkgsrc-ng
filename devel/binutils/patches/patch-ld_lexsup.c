$NetBSD$

--- ld/lexsup.c.orig	Mon Mar 25 08:06:23 2013
+++ ld/lexsup.c
@@ -398,7 +398,7 @@ static const struct ld_option ld_options[] =
     ONE_DASH },
   { {"shared", no_argument, NULL, OPTION_SHARED},
     '\0', NULL, N_("Create a shared library"), ONE_DASH },
-  { {"Bshareable", no_argument, NULL, OPTION_SHARED }, /* FreeBSD.  */
+  { {"Bshareable", no_argument, NULL, OPTION_SHARED }, /* FreeBSD, NetBSD.  */
     '\0', NULL, NULL, ONE_DASH },
   { {"pie", no_argument, NULL, OPTION_PIE},
     '\0', NULL, N_("Create a position independent executable"), ONE_DASH },
@@ -496,8 +496,14 @@ static const struct ld_option ld_options[] =
   { {"whole-archive", no_argument, NULL, OPTION_WHOLE_ARCHIVE},
     '\0', NULL, N_("Include all objects from following archives"),
     TWO_DASHES },
+  { {"Bforcearchive", no_argument, NULL, OPTION_WHOLE_ARCHIVE},
+      '\0', NULL, NULL, TWO_DASHES },	/* NetBSD.  */
   { {"wrap", required_argument, NULL, OPTION_WRAP},
     '\0', N_("SYMBOL"), N_("Use wrapper functions for SYMBOL"), TWO_DASHES },
+  { {"ignore-unresolved-symbol", required_argument, NULL,
+    OPTION_IGNORE_UNRESOLVED_SYMBOL},
+    '\0', N_("SYMBOL"),
+    N_("Unresolved SYMBOL will not cause an error or warning"), TWO_DASHES },
 };
 
 #define OPTION_COUNT ARRAY_SIZE (ld_options)
@@ -1343,6 +1349,9 @@ parse_args (unsigned argc, char **argv)
 	  break;
 	case OPTION_WRAP:
 	  add_wrap (optarg);
+	  break;
+	case OPTION_IGNORE_UNRESOLVED_SYMBOL:
+	  add_ignoresym (optarg);
 	  break;
 	case OPTION_DISCARD_NONE:
 	  link_info.discard = discard_none;
