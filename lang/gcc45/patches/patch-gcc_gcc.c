$NetBSD$

--- gcc/gcc.c.orig	Sun Apr 18 17:46:08 2010
+++ gcc/gcc.c
@@ -1760,7 +1760,7 @@ init_gcc_specs (struct obstack *obstack, const char *s
 		static_name, " --as-needed ", shared_name, " --no-as-needed"
 		"}"
 		"%{shared-libgcc:",
-		shared_name, "%{!shared: ", static_name, "}"
+		"--as-needed ", shared_name, " --no-as-needed ", static_name,
 		"}"
 #else
 		"%{!shared:"
@@ -3154,10 +3154,11 @@ execute (void)
 	    else
 #endif
 	      fatal_ice ("\
-Internal error: %s (program %s)\n\
+Internal error: %s (program %s received signal %d)\n\
 Please submit a full bug report.\n\
 See %s for instructions.",
 		 	strsignal (WTERMSIG (status)), commands[i].prog,
+			WTERMSIG (status),
 		 	bug_report_url);
 	  }
 	else if (WIFEXITED (status)
@@ -3629,6 +3630,10 @@ process_command (int argc, const char **argv)
   /* FIXME: make_relative_prefix doesn't yet work for VMS.  */
   if (!gcc_exec_prefix)
     {
+#ifdef NETBSD_NATIVE
+      add_prefix (&exec_prefixes, standard_libexec_prefix, "GCC",
+		  PREFIX_PRIORITY_LAST, 0, 0);
+#else
       gcc_exec_prefix = get_relative_prefix (argv[0],
 					     standard_bindir_prefix,
 					     standard_exec_prefix);
@@ -3637,6 +3642,7 @@ process_command (int argc, const char **argv)
 					     standard_libexec_prefix);
       if (gcc_exec_prefix)
 	xputenv (concat ("GCC_EXEC_PREFIX=", gcc_exec_prefix, NULL));
+#endif
     }
   else
     {
@@ -6938,6 +6944,7 @@ main (int argc, char **argv)
   else
     init_spec ();
 
+#ifndef NETBSD_NATIVE
   /* We need to check standard_exec_prefix/just_machine_suffix/specs
      for any override of as, ld and libraries.  */
   specs_file = (char *) alloca (strlen (standard_exec_prefix)
@@ -6948,6 +6955,7 @@ main (int argc, char **argv)
   strcat (specs_file, "specs");
   if (access (specs_file, R_OK) == 0)
     read_specs (specs_file, TRUE);
+#endif
 
   /* Process any configure-time defaults specified for the command line
      options, via OPTION_DEFAULT_SPECS.  */
@@ -7077,14 +7085,18 @@ main (int argc, char **argv)
 			      PREFIX_PRIORITY_LAST, 0, 1);
       else if (*cross_compile == '0')
 	{
+/* XXXMRG not sure this one is right? */
+#if !defined(NETBSD_NATIVE) && !defined(NETBSD_TOOLS)
 	  add_prefix (&startfile_prefixes,
 		      concat (gcc_exec_prefix
 			      ? gcc_exec_prefix : standard_exec_prefix,
 			      machine_suffix,
 			      standard_startfile_prefix, NULL),
 		      NULL, PREFIX_PRIORITY_LAST, 0, 1);
+#endif /* NETBSD_NATIVE */
 	}
 
+#if !defined(NETBSD_NATIVE) && !defined(NETBSD_TOOLS)
       /* Sysrooted prefixes are relocated because target_system_root is
 	 also relocated by gcc_exec_prefix.  */
       if (*standard_startfile_prefix_1)
@@ -7095,6 +7107,7 @@ main (int argc, char **argv)
 	add_sysrooted_prefix (&startfile_prefixes,
 			      standard_startfile_prefix_2, "BINUTILS",
 			      PREFIX_PRIORITY_LAST, 0, 1);
+#endif /* NETBSD_NATIVE */
     }
 
   /* Process any user specified specs in the order given on the command
