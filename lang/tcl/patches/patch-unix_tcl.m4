$NetBSD$

--- unix/tcl.m4.orig	Thu Sep 19 20:17:13 2013
+++ unix/tcl.m4
@@ -1520,7 +1520,7 @@ AC_DEFUN([SC_CONFIG_CFLAGS], [
 	    UNSHARED_LIB_SUFFIX='${TCL_TRIM_DOTS}.a'
 	    TCL_LIB_VERSIONS_OK=nodots
 	    ;;
-	NetBSD-*)
+	Minix-*|NetBSD-*)
 	    # NetBSD has ELF and can use 'cc -shared' to build shared libs
 	    SHLIB_CFLAGS="-fPIC"
 	    SHLIB_LD='${CC} -shared ${SHLIB_CFLAGS}'
@@ -1538,7 +1538,7 @@ AC_DEFUN([SC_CONFIG_CFLAGS], [
 	    	LDFLAGS="$LDFLAGS -pthread"
 	    ])
 	    ;;
-	FreeBSD-*)
+	FreeBSD-*|DragonFly-*)
 	    # This configuration from FreeBSD Ports.
 	    SHLIB_CFLAGS="-fPIC"
 	    SHLIB_LD="${CC} -shared"
@@ -2031,7 +2031,7 @@ dnl # preprocessing tests use only CPPFLAGS.
 	    BSD/OS*) ;;
 	    CYGWIN_*|MINGW32_*) ;;
 	    IRIX*) ;;
-	    NetBSD-*|FreeBSD-*|OpenBSD-*) ;;
+	    Minix-*|NetBSD-*|FreeBSD-*|OpenBSD-*) ;;
 	    Darwin-*) ;;
 	    SCO_SV-3.2*) ;;
 	    *) SHLIB_CFLAGS="-fPIC" ;;
