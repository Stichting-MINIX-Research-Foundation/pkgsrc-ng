$NetBSD$

--- gcc/config/m68k/lb1sf68.asm.orig	Fri Oct  2 11:20:51 2009
+++ gcc/config/m68k/lb1sf68.asm
@@ -202,6 +202,8 @@ see the files COPYING3 and COPYING.RUNTIME respectivel
 #if defined (__mcoldfire__) && !defined (__mcfisab__) && !defined (__mcfisac__)
 	lea	\addr-.-8,a0
 	jsr	pc@(a0)
+#elif defined(__NetBSD__)
+	jbsr	\addr@PLTPC
 #else
 	jbsr	\addr
 #endif
@@ -211,9 +213,11 @@ see the files COPYING3 and COPYING.RUNTIME respectivel
 	/* ISA C has no bra.l instruction, and since this assembly file
 	   gets assembled into multiple object files, we avoid the
 	   bra instruction entirely.  */
-#if defined (__mcoldfire__) && !defined (__mcfisab__)
+#if (defined (__mcoldfire__) && !defined (__mcfisab__))
 	lea	\addr-.-8,a0
 	jmp	pc@(a0)
+#elif defined(__NetBSD__)
+	bra	\addr@PLTPC
 #else
 	bra	\addr
 #endif
