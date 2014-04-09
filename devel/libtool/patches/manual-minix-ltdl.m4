--- libltdl/m4/ltdl.m4.nbsd	Wed Apr  9 10:59:05 2014
+++ libltdl/m4/ltdl.m4	Wed Apr  9 11:09:44 2014
@@ -496,7 +496,7 @@
   mirbsd*)
     lt_cv_sys_dlopen_deplibs=yes
     ;;
-  netbsd*)
+  netbsd* | minix*)
     lt_cv_sys_dlopen_deplibs=yes
     ;;
   openbsd*)
