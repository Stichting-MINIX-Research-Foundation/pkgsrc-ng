$NetBSD$

--- gcc/config/pa/milli64.S.orig	Thu Apr  9 15:00:19 2009
+++ gcc/config/pa/milli64.S
@@ -221,7 +221,7 @@ GSYM($$dyncall)
 	ldw	4(%r22),%r19		; load new LTP value
 	ldw	0(%r22),%r22		; load address of target
 LSYM(1)
-#ifdef LINUX
+#if defined(LINUX) || defined(NETBSD)
 	bv	%r0(%r22)		; branch to the real target
 #else
 	ldsid	(%sr0,%r22),%r1		; get the "space ident" selected by r22
