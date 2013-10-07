$NetBSD$

--- gas/atof-generic.c.orig	Wed Sep  2 07:24:19 2009
+++ gas/atof-generic.c
@@ -121,6 +121,32 @@ atof_generic (/* return pointer to just AFTER number w
 
   switch (first_digit[0])
     {
+    case 's':
+    case 'S':
+      if (!strncasecmp ("snan", first_digit, 4))
+	{
+	  address_of_generic_floating_point_number->sign = 0;
+	  address_of_generic_floating_point_number->exponent = 0;
+	  address_of_generic_floating_point_number->leader =
+	    address_of_generic_floating_point_number->low;
+	  *address_of_string_pointer = first_digit + 4;
+	  return 0;
+	}
+      break;
+
+    case 'q':
+    case 'Q':
+      if (!strncasecmp ("qnan", first_digit, 4))
+	{
+	  address_of_generic_floating_point_number->sign = 0;
+	  address_of_generic_floating_point_number->exponent = 0;
+	  address_of_generic_floating_point_number->leader =
+	    address_of_generic_floating_point_number->low;
+	  *address_of_string_pointer = first_digit + 4;
+	  return 0;
+	}
+      break;
+
     case 'n':
     case 'N':
       if (!strncasecmp ("nan", first_digit, 3))
