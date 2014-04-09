--- ./libltdl/m4/libtool.m4.nbsd	Wed Apr  9 10:58:58 2014
+++ ./libltdl/m4/libtool.m4	Wed Apr  9 11:06:53 2014
@@ -1641,7 +1641,7 @@
     lt_cv_sys_max_cmd_len=8192;
     ;;
 
-  netbsd* | freebsd* | openbsd* | mirbsd* | darwin* | dragonfly*)
+  netbsd* | freebsd* | openbsd* | minix* | mirbsd* | darwin* | dragonfly*)
     # This has been around since 386BSD, at least.  Likely further.
     if test -x /sbin/sysctl; then
       lt_cv_sys_max_cmd_len=`/sbin/sysctl -n kern.argmax`
@@ -2728,6 +2728,18 @@
   hardcode_into_libs=yes
   ;;
 
+minix*)
+  version_type=linux
+  need_lib_prefix=no
+  need_version=no
+  library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major ${libname}${shared_ext}'
+  soname_spec='${libname}${release}${shared_ext}$major'
+  dynamic_linker='Minix ld.elf_so'
+  shlibpath_var=LD_LIBRARY_PATH
+  shlibpath_overrides_runpath=yes
+  hardcode_into_libs=yes
+  ;;
+
 newsos6)
   version_type=linux # correct to gnu/linux during the next big refactor
   library_names_spec='${libname}${release}${shared_ext}$versuffix ${libname}${release}${shared_ext}$major $libname${shared_ext}'
@@ -3326,7 +3338,7 @@
   lt_cv_deplibs_check_method='match_pattern /lib[[^/]]+(\.so\.[[0-9]]+\.[[0-9]]+|\.so|_pic\.a)$'
   ;;
 
-netbsd*)
+netbsd* | minix*)
   lt_cv_deplibs_check_method='match_pattern /lib[[^/]]+(\.so|_pic\.a)$'
   ;;
 
@@ -4143,7 +4155,7 @@
 	    ;;
 	esac
 	;;
-      netbsd*)
+      netbsd* | minix*)
 	;;
       *qnx* | *nto*)
         # QNX uses GNU C++, but need to define -shared option too, otherwise
@@ -4943,7 +4955,7 @@
       fi
       ;;
 
-    netbsd*)
+    netbsd* | minix*)
       _LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
       _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
       _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
@@ -5437,7 +5449,7 @@
       fi
       ;;
 
-    netbsd*)
+    netbsd* | minix*)
       _LT_TAGVAR(archive_cmds, $1)='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
       _LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
       _LT_TAGVAR(hardcode_libdir_flag_spec, $1)='${wl}-rpath,$libdir'
@@ -6662,7 +6674,7 @@
 	esac
 	;;
 
-      netbsd*)
+      netbsd* | minix*)
 	_LT_TAGVAR(ld_shlibs, $1)=yes
 	_LT_TAGVAR(archive_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname -o $lib'
 	_LT_TAGVAR(archive_expsym_cmds, $1)='$CC -shared $pic_flag $libobjs $deplibs $compiler_flags ${wl}-soname $wl$soname ${wl}-retain-symbols-file $wl$export_symbols -o $lib'
