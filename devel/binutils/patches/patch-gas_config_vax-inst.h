$NetBSD$

--- gas/config/vax-inst.h.orig	Wed Sep  2 07:24:21 2009
+++ gas/config/vax-inst.h
@@ -66,6 +66,8 @@ typedef long vax_opcodeT;	/* For initialising array of
 #define VAX_WIDEN_WORD (0x20)	/* Add this to byte branch to get word br.  */
 #define VAX_WIDEN_LONG (0x6)	/* Add this to byte branch to get long jmp.*/
 /* Needs VAX_PC_RELATIVE_MODE byte after it*/
+#define	VAX_CALLS (0xFB)	/* Call with arg list on stack	           */
+#define	VAX_CALLG (0xFA)	/* Call with arg list in memory		   */
 
 struct vit			/* vax instruction tree                    */
 {
