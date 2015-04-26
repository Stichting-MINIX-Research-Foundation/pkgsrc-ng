$NetBSD$

--- gprof/corefile.c.orig	Tue Mar  6 13:54:59 2012
+++ gprof/corefile.c
@@ -30,6 +30,8 @@
 #include "corefile.h"
 #include "safe-ctype.h"
 
+#include <stdlib.h>
+
 bfd *core_bfd;
 static int core_num_syms;
 static asymbol **core_syms;
