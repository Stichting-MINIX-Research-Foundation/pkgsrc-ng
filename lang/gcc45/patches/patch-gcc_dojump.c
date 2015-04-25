$NetBSD$

--- gcc/dojump.c.orig	Fri Feb 19 18:19:06 2010
+++ gcc/dojump.c
@@ -1022,7 +1022,7 @@ do_compare_rtx_and_jump (rtx op0, rtx op1, enum rtx_co
     }
   else
     {
-      if (GET_MODE_CLASS (mode) == MODE_FLOAT
+      if (SCALAR_FLOAT_MODE_P (mode)
 	  && ! can_compare_p (code, mode, ccp_jump)
 	  && can_compare_p (swap_condition (code), mode, ccp_jump))
 	{
@@ -1033,7 +1033,7 @@ do_compare_rtx_and_jump (rtx op0, rtx op1, enum rtx_co
 	  op1 = tmp;
 	}
 
-      else if (GET_MODE_CLASS (mode) == MODE_FLOAT
+      else if (SCALAR_FLOAT_MODE_P (mode)
 	       && ! can_compare_p (code, mode, ccp_jump)
 
 	       /* Never split ORDERED and UNORDERED.  These must be implemented.  */
