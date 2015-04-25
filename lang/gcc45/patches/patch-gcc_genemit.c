$NetBSD$

--- gcc/genemit.c.orig	Fri Nov 27 11:37:06 2009
+++ gcc/genemit.c
@@ -250,9 +250,9 @@ gen_exp (rtx x, enum rtx_code subroutine_type, char *u
 	printf ("const_true_rtx");
       else
 	{
-	  printf ("GEN_INT (");
-	  printf (HOST_WIDE_INT_PRINT_DEC_C, INTVAL (x));
-	  printf (")");
+	  printf ("GEN_INT (HOST_WIDE_INT_CONSTANT (");
+	  printf (HOST_WIDE_INT_PRINT_DEC, INTVAL (x));
+	  printf ("))");
 	}
       return;
 
