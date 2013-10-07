$NetBSD$

--- ld/emultempl/elf32.em.orig	Mon Mar 25 08:06:23 2013
+++ ld/emultempl/elf32.em
@@ -72,6 +72,9 @@ EOF
 
 if [ "x${USE_LIBPATH}" = xyes ] ; then
   case ${target} in
+    *-*-netbsd*)
+    ;;
+
     *-*-linux-* | *-*-k*bsd*-* | *-*-gnu*)
   fragment <<EOF
 #ifdef HAVE_GLOB
@@ -103,6 +106,7 @@ gld${EMULATION_NAME}_before_parse (void)
 {
   ldfile_set_output_arch ("${OUTPUT_ARCH}", bfd_arch_`echo ${ARCH} | sed -e 's/:.*//'`);
   input_flags.dynamic = ${DYNAMIC_LINK-TRUE};
+  input_flags.add_DT_NEEDED_for_dynamic = TRUE;
   config.has_shared = `if test -n "$GENERATE_SHLIB_SCRIPT" ; then echo TRUE ; else echo FALSE ; fi`;
   config.separate_code = `if test "x${SEPARATE_CODE}" = xyes ; then echo TRUE ; else echo FALSE ; fi`;
 }
@@ -375,6 +379,9 @@ gld${EMULATION_NAME}_try_needed (struct dt_needed *nee
 
 EOF
 case ${target} in
+    *-*-netbsd*)
+    ;;
+
   *-*-linux-* | *-*-k*bsd*-* | *-*-gnu*)
     fragment <<EOF
 	  {
@@ -454,15 +461,25 @@ fragment <<EOF
 
 static bfd_boolean
 gld${EMULATION_NAME}_search_needed (const char *path,
-				    struct dt_needed *n, int force)
+				    struct dt_needed *n, int force, int prepend_sysroot)
 {
   const char *s;
   const char *name = n->name;
   size_t len;
   struct dt_needed needed;
 
-  if (name[0] == '/')
+  if (name[0] == '/') {
+    if (prepend_sysroot && ld_sysroot) {
+      bfd_boolean rv;
+      needed.by = n->by;
+      char *filename= concat(ld_sysroot, n->name, (const char *)NULL);
+      needed.name = filename;
+      rv = gld${EMULATION_NAME}_try_needed (&needed, force);
+      free(filename);
+      return rv;
+    }
     return gld${EMULATION_NAME}_try_needed (n, force);
+  }
 
   if (path == NULL || *path == '\0')
     return FALSE;
@@ -501,6 +518,13 @@ gld${EMULATION_NAME}_search_needed (const char *path,
 	}
       strcpy (sset, name);
 
+      if (prepend_sysroot && filename[0] == '=')
+        abort();
+      if (filename[0] == '/' && prepend_sysroot && ld_sysroot) {
+        char *filename2 = concat(ld_sysroot, filename, (const char *)NULL);
+        free(filename);
+        filename = filename2;
+      }
       needed.name = filename;
       if (gld${EMULATION_NAME}_try_needed (&needed, force))
 	return TRUE;
@@ -621,6 +645,9 @@ EOF
     # FreeBSD
     ;;
 
+    *-*-netbsd*)
+    ;;
+
     *-*-linux-* | *-*-k*bsd*-* | *-*-gnu*)
       fragment <<EOF
 /* For a native linker, check the file /etc/ld.so.conf for directories
@@ -1262,13 +1289,13 @@ fi
 fragment <<EOF
 
 	  if (gld${EMULATION_NAME}_search_needed (command_line.rpath_link,
-						  &n, force))
+						  &n, force, 0))
 	    break;
 EOF
 if [ "x${USE_LIBPATH}" = xyes ] ; then
 fragment <<EOF
 	  if (gld${EMULATION_NAME}_search_needed (command_line.rpath,
-						  &n, force))
+						  &n, force, 1))
 	    break;
 EOF
 fi
@@ -1279,11 +1306,11 @@ fragment <<EOF
 	    {
 	      lib_path = (const char *) getenv ("LD_RUN_PATH");
 	      if (gld${EMULATION_NAME}_search_needed (lib_path, &n,
-						      force))
+						      force, 0))
 		break;
 	    }
 	  lib_path = (const char *) getenv ("LD_LIBRARY_PATH");
-	  if (gld${EMULATION_NAME}_search_needed (lib_path, &n, force))
+	  if (gld${EMULATION_NAME}_search_needed (lib_path, &n, force, 0))
 	    break;
 EOF
 fi
@@ -1293,12 +1320,10 @@ fragment <<EOF
 	  rp = bfd_elf_get_runpath_list (link_info.output_bfd, &link_info);
 	  for (; !found && rp != NULL; rp = rp->next)
 	    {
-	      char *tmpname = gld${EMULATION_NAME}_add_sysroot (rp->name);
 	      found = (rp->by == l->by
-		       && gld${EMULATION_NAME}_search_needed (tmpname,
+		       && gld${EMULATION_NAME}_search_needed (rp->name,
 							      &n,
-							      force));
-	      free (tmpname);
+							      force, 1));
 	    }
 	  if (found)
 	    break;
@@ -1315,6 +1340,9 @@ EOF
     # FreeBSD
     ;;
 
+    *-*-netbsd*)
+    ;;
+
     *-*-linux-* | *-*-k*bsd*-* | *-*-gnu*)
     # Linux
       fragment <<EOF
@@ -1515,7 +1543,8 @@ gld${EMULATION_NAME}_before_allocation (void)
 	   a dep audit entry.  */
 	if (audit_libs && *audit_libs != '\0')
 	  {
-	    char *cp = xstrdup (audit_libs);
+	    char *cp, *fcp;
+	    fcp = cp = xstrdup (audit_libs);
 	    do
 	      {
 		int more = 0;
@@ -1533,6 +1562,7 @@ gld${EMULATION_NAME}_before_allocation (void)
 		cp = more ? ++cp2 : NULL;
 	      }
 	    while (cp != NULL);
+	    free (fcp);
 	  }
       }
 
