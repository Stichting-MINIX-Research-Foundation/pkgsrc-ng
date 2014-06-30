$NetBSD$
--- Source/kwsys/SystemInformation.cxx.orig	Thu Jan 16 17:15:08 2014
+++ Source/kwsys/SystemInformation.cxx	Fri Jul 11 06:22:41 2014
@@ -78,9 +78,9 @@ typedef int siginfo_t;
 # include <errno.h> // extern int errno;
 #endif
 
-#ifdef __FreeBSD__
+#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__minix) || defined(__FreeBSD__) || defined(__DragonFly__)
+# include <sys/param.h>
 # include <sys/sysctl.h>
-# include <fenv.h>
 # include <sys/socket.h>
 # include <netdb.h>
 # include <netinet/in.h>
@@ -88,11 +88,15 @@ typedef int siginfo_t;
 #  include <ifaddrs.h>
 #  define KWSYS_SYSTEMINFORMATION_IMPLEMENT_FQDN
 # endif
-#endif
-
-#if defined(__OpenBSD__) || defined(__NetBSD__)
-# include <sys/param.h>
-# include <sys/sysctl.h>
+# if defined(KWSYS_SYSTEMINFORMATION_HAS_BACKTRACE)
+#  include <execinfo.h>
+#  if defined(KWSYS_SYSTEMINFORMATION_HAS_CPP_DEMANGLE)
+#    include <cxxabi.h>
+#  endif
+#  if defined(KWSYS_SYSTEMINFORMATION_HAS_SYMBOL_LOOKUP)
+#    include <dlfcn.h>
+#  endif
+# endif
 #endif
 
 #if defined(KWSYS_SYS_HAS_MACHINE_CPU_H)
@@ -130,7 +134,7 @@ typedef int siginfo_t;
 # endif
 #endif
 
-#ifdef __linux
+#if defined(__linux) || defined (__sun)
 # include <fenv.h>
 # include <sys/socket.h>
 # include <netdb.h>
@@ -3679,7 +3683,11 @@
     // install ours
     struct sigaction sa;
     sa.sa_sigaction=(SigAction)StacktraceSignalHandler;
+#if defined(__minix)
+    sa.sa_flags=SA_RESTART|SA_RESETHAND;
+#else
     sa.sa_flags=SA_SIGINFO|SA_RESTART|SA_RESETHAND;
+#endif
     sigemptyset(&sa.sa_mask);
 
     sigaction(SIGABRT,&sa,0);
@@ -4616,7 +4624,7 @@ bool SystemInformationImplementation::Qu
   // a 32 bit process on a 64 bit host the returned memory will be
   // limited to 4GiB. So if this is a 32 bit process or if the sysconf
   // method fails use the kstat interface.
-#if SIZEOF_VOID_P == 8
+#if CMAKE_SIZEOF_VOID_P == 8
   if (this->QueryMemoryBySysconf())
     {
     return true;
