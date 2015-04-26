$NetBSD$

--- gas/config/atof-vax.c.orig	Wed Oct 17 16:45:54 2007
+++ gas/config/atof-vax.c
@@ -268,10 +268,27 @@ flonum_gen2vax (int format_letter,	/* One of 'd' 'f' '
 	  int exponent_skippage;
 	  LITTLENUM_TYPE word1;
 
-	  /* JF: Deal with new Nan, +Inf and -Inf codes.  */
 	  if (f->sign != '-' && f->sign != '+')
 	    {
-	      make_invalid_floating_point_number (words);
+	      if (f->sign == 0)
+		{
+		  /* All NaNs are 0.  */
+		  memset (words, 0x00, sizeof (LITTLENUM_TYPE) * precision);
+		}
+	      else if (f->sign == 'P')
+		{
+		  /* Positive Infinity.  */
+		  memset (words, 0xff, sizeof (LITTLENUM_TYPE) * precision);
+		  words[0] &= 0x7fff;
+		}
+	      else if (f->sign == 'N')
+		{
+		  /* Negative Infinity.  */
+		  memset (words, 0x00, sizeof (LITTLENUM_TYPE) * precision);
+		  words[0] = 0x0080;
+		}
+	      else
+		make_invalid_floating_point_number (words);
 	      return return_value;
 	    }
 
