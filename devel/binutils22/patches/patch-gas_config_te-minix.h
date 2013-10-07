$NetBSD$

--- gas/config/te-minix.h.orig	Mon Sep 23 18:17:54 2013
+++ gas/config/te-minix.h
@@ -0,0 +1,9 @@
+#define TE_MINIX 1
+
+/* Added these, because if we don't know what we're targeting we may
+   need an assembler version of libgcc, and that will use local
+   labels.  */
+#define LOCAL_LABELS_DOLLAR 1
+#define LOCAL_LABELS_FB 1
+
+#include "obj-format.h"
