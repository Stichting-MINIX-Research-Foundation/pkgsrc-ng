$NetBSD$

--- binutils/aclocal.m4.orig	Thu May 17 22:23:39 2012
+++ binutils/aclocal.m4
@@ -1,4 +1,4 @@
-# generated automatically by aclocal 1.11.1 -*- Autoconf -*-
+# generated automatically by aclocal 1.11 -*- Autoconf -*-
 
 # Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004,
 # 2005, 2006, 2007, 2008, 2009  Free Software Foundation, Inc.
@@ -19,6 +19,31 @@ You have another version of autoconf.  It may work, bu
 If you have problems, you may need to regenerate the build system entirely.
 To do so, use the procedure documented by the package, typically `autoreconf'.])])
 
+# isc-posix.m4 serial 2 (gettext-0.11.2)
+dnl Copyright (C) 1995-2002 Free Software Foundation, Inc.
+dnl This file is free software; the Free Software Foundation
+dnl gives unlimited permission to copy and/or distribute it,
+dnl with or without modifications, as long as this notice is preserved.
+
+# This file is not needed with autoconf-2.53 and newer.  Remove it in 2005.
+
+# This test replaces the one in autoconf.
+# Currently this macro should have the same name as the autoconf macro
+# because gettext's gettext.m4 (distributed in the automake package)
+# still uses it.  Otherwise, the use in gettext.m4 makes autoheader
+# give these diagnostics:
+#   configure.in:556: AC_TRY_COMPILE was called before AC_ISC_POSIX
+#   configure.in:556: AC_TRY_RUN was called before AC_ISC_POSIX
+
+undefine([AC_ISC_POSIX])
+
+AC_DEFUN([AC_ISC_POSIX],
+  [
+    dnl This test replaces the obsolescent AC_ISC_POSIX kludge.
+    AC_CHECK_LIB(cposix, strerror, [LIBS="$LIBS -lcposix"])
+  ]
+)
+
 # Copyright (C) 2002, 2003, 2005, 2006, 2007, 2008  Free Software Foundation, Inc.
 #
 # This file is free software; the Free Software Foundation
@@ -34,7 +59,7 @@ AC_DEFUN([AM_AUTOMAKE_VERSION],
 [am__api_version='1.11'
 dnl Some users find AM_AUTOMAKE_VERSION and mistake it for a way to
 dnl require some minimum version.  Point them to the right macro.
-m4_if([$1], [1.11.1], [],
+m4_if([$1], [1.11], [],
       [AC_FATAL([Do not call $0, use AM_INIT_AUTOMAKE([$1]).])])dnl
 ])
 
@@ -50,7 +75,7 @@ m4_define([_AM_AUTOCONF_VERSION], [])
 # Call AM_AUTOMAKE_VERSION and AM_AUTOMAKE_VERSION so they can be traced.
 # This function is AC_REQUIREd by AM_INIT_AUTOMAKE.
 AC_DEFUN([AM_SET_CURRENT_AUTOMAKE_VERSION],
-[AM_AUTOMAKE_VERSION([1.11.1])dnl
+[AM_AUTOMAKE_VERSION([1.11])dnl
 m4_ifndef([AC_AUTOCONF_VERSION],
   [m4_copy([m4_PACKAGE_VERSION], [AC_AUTOCONF_VERSION])])dnl
 _AM_AUTOCONF_VERSION(m4_defn([AC_AUTOCONF_VERSION]))])
