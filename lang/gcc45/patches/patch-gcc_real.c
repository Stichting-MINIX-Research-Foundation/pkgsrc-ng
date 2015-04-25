$NetBSD$

--- gcc/real.c.orig	Wed Nov 25 10:55:54 2009
+++ gcc/real.c
@@ -1008,15 +1008,25 @@ real_arithmetic (REAL_VALUE_TYPE *r, int icode, const 
   switch (code)
     {
     case PLUS_EXPR:
+      /* Clear any padding areas in *r if it isn't equal to one of the
+	 operands so that we can later do bitwise comparisons later on.  */
+      if (r != op0 && r != op1)
+	memset (r, '\0', sizeof (*r));
       return do_add (r, op0, op1, 0);
 
     case MINUS_EXPR:
+      if (r != op0 && r != op1)
+	memset (r, '\0', sizeof (*r));
       return do_add (r, op0, op1, 1);
 
     case MULT_EXPR:
+      if (r != op0 && r != op1)
+	memset (r, '\0', sizeof (*r));
       return do_multiply (r, op0, op1);
 
     case RDIV_EXPR:
+      if (r != op0 && r != op1)
+	memset (r, '\0', sizeof (*r));
       return do_divide (r, op0, op1);
 
     case MIN_EXPR:
