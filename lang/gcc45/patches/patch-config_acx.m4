$NetBSD$

--- config/acx.m4.orig	Fri Oct 23 10:03:47 2009
+++ config/acx.m4
@@ -356,9 +356,9 @@ m4_define([AC_CHECK_HEADER],m4_defn([_AC_CHECK_HEADER_
 ac_c_preproc_warn_flag=yes])# AC_PROG_CPP_WERROR
 
 # Test for GNAT.
-# We require the gnatbind program, and a compiler driver that
-# understands Ada.  We use the user's CC setting, already found,
-# and possibly add $1 to the command-line parameters.
+# We require the gnatbind & gnatmake programs, as well as a compiler driver
+# that understands Ada.  We use the user's CC setting, already found, and
+# possibly add $1 to the command-line parameters.
 #
 # Sets the shell variable have_gnat to yes or no as appropriate, and
 # substitutes GNATBIND and GNATMAKE.
@@ -387,7 +387,7 @@ if test x"$errors" = x && test -f conftest.$ac_objext;
 fi
 rm -f conftest.*])
 
-if test x$GNATBIND != xno && test x$GNATMAKE != xno && test x$acx_cv_cc_gcc_supports_ada != xno; then
+if test "x$GNATBIND" != xno && test "x$GNATMAKE" != xno && test x$acx_cv_cc_gcc_supports_ada != xno; then
   have_gnat=yes
 else
   have_gnat=no
