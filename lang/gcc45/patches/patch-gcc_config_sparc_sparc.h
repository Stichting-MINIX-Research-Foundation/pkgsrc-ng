$NetBSD$

--- gcc/config/sparc/sparc.h.orig	Sun Dec 19 12:20:08 2010
+++ gcc/config/sparc/sparc.h
@@ -414,6 +414,7 @@ extern enum cmodel sparc_cmodel;
 %{mcpu=sparclite:-Asparclite} \
 %{mcpu=sparclite86x:-Asparclite} \
 %{mcpu=f930:-Asparclite} %{mcpu=f934:-Asparclite} \
+%{mcpu=v8:-Av8} \
 %{mv8plus:-Av8plus} \
 %{mcpu=v9:-Av9} \
 %{mcpu=ultrasparc:%{!mv8plus:-Av9a}} \
@@ -501,7 +502,8 @@ extern enum cmodel sparc_cmodel;
 #define CAN_DEBUG_WITHOUT_FP
 
 /* Option handling.  */
-
+#define OPTIMIZATION_OPTIONS(LEVEL, SIZE) \
+  sparc_optimization_options ((LEVEL), (SIZE))
 #define OVERRIDE_OPTIONS  sparc_override_options ()
 
 /* Mask of all CPU selection flags.  */
