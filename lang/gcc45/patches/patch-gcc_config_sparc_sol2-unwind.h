$NetBSD$

--- gcc/config/sparc/sol2-unwind.h.orig	Wed Oct 27 20:34:57 2010
+++ gcc/config/sparc/sol2-unwind.h
@@ -123,10 +123,10 @@ sparc64_fallback_frame_state (struct _Unwind_Context *
 	  /* This matches the call_user_handler pattern for Solaris 10.
 	     There are 2 cases so we look for the return address of the
 	     caller's caller frame in order to do more pattern matching.  */
-	  unsigned int sah_pattern
-	    = *(unsigned int *)(*(unsigned long *)(this_cfa + 176 + 15*8) - 4);
+	  unsigned long sah_address
+	    = *(unsigned long *)(this_cfa + 176 + 15*8);
 
-          if (sah_pattern == 0x92100019)
+          if (sah_address && *(unsigned int *)(sah_address - 4) == 0x92100019)
 	    /* This is the same setup as for Solaris 9, see below.  */
 	    regs_off = 176 + 176 + 176 + 304;
 	  else
@@ -371,10 +371,10 @@ sparc_fallback_frame_state (struct _Unwind_Context *co
 	  /* This matches the call_user_handler pattern for Solaris 10.
 	     There are 2 cases so we look for the return address of the
 	     caller's caller frame in order to do more pattern matching.  */
-	  unsigned int sah_pattern
-	    = *(unsigned int *)(*(unsigned int *)(this_cfa + 96 + 15*4) - 4);
+	  unsigned int sah_address
+	    = *(unsigned int *)(this_cfa + 96 + 15*4);
 
-          if (sah_pattern == 0x92100019)
+          if (sah_address && *(unsigned int *)(sah_address - 4) == 0x92100019)
 	    /* This is the same setup as for Solaris 9, see below.  */
 	    regs_off = 96 + 96 + 96 + 160;
 	  else
