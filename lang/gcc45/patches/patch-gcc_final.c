$NetBSD$

--- gcc/final.c.orig	Fri Mar 26 16:18:51 2010
+++ gcc/final.c
@@ -2241,6 +2241,11 @@ final_scan_insn (rtx insn, FILE *file, int optimize AT
 	    location_t loc;
 	    expanded_location expanded;
 
+	    /* Make sure we flush any queued register saves in case this
+	       clobbers affected registers.  */
+	    if (dwarf2out_do_frame ())
+	      dwarf2out_frame_debug (insn, false);
+
 	    /* There's no telling what that did to the condition codes.  */
 	    CC_STATUS_INIT;
 
