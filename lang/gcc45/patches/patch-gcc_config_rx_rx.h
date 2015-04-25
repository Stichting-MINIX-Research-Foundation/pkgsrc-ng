$NetBSD$

--- gcc/config/rx/rx.h.orig	Thu Mar 17 10:51:26 2011
+++ gcc/config/rx/rx.h
@@ -168,7 +168,7 @@ extern enum rx_cpu_types  rx_cpu_type;
 
 #define HANDLE_PRAGMA_PACK_PUSH_POP	1
 
-#define HAVE_PRE_DECCREMENT		1
+#define HAVE_PRE_DECREMENT		1
 #define HAVE_POST_INCREMENT		1
 
 #define MOVE_RATIO(SPEED) 		((SPEED) ? 4 : 2)
