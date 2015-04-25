$NetBSD$

--- gcc/combine.c.orig	Tue Dec  7 15:08:54 2010
+++ gcc/combine.c
@@ -5298,7 +5298,7 @@ combine_simplify_rtx (rtx x, enum machine_mode op0_mod
 	{
 	  /* Try to simplify the expression further.  */
 	  rtx tor = simplify_gen_binary (IOR, mode, XEXP (x, 0), XEXP (x, 1));
-	  temp = combine_simplify_rtx (tor, mode, in_dest);
+	  temp = combine_simplify_rtx (tor, VOIDmode, in_dest);
 
 	  /* If we could, great.  If not, do not go ahead with the IOR
 	     replacement, since PLUS appears in many special purpose
