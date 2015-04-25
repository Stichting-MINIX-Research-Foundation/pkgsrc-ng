$NetBSD$

--- gcc/config/rs6000/vsx.md.orig	Fri Feb  4 16:31:48 2011
+++ gcc/config/rs6000/vsx.md
@@ -844,7 +844,7 @@
   [(set (match_operand:VSX_L 0 "vsx_register_operand" "=<VSr>,?wa")
 	(if_then_else:VSX_L
 	 (ne:CC (match_operand:VSX_L 1 "vsx_register_operand" "<VSr>,wa")
-		(const_int 0))
+		(match_operand:VSX_L 4 "zero_constant" ""))
 	 (match_operand:VSX_L 2 "vsx_register_operand" "<VSr>,wa")
 	 (match_operand:VSX_L 3 "vsx_register_operand" "<VSr>,wa")))]
   "VECTOR_MEM_VSX_P (<MODE>mode)"
@@ -855,7 +855,7 @@
   [(set (match_operand:VSX_L 0 "vsx_register_operand" "=<VSr>,?wa")
 	(if_then_else:VSX_L
 	 (ne:CCUNS (match_operand:VSX_L 1 "vsx_register_operand" "<VSr>,wa")
-		   (const_int 0))
+		   (match_operand:VSX_L 4 "zero_constant" ""))
 	 (match_operand:VSX_L 2 "vsx_register_operand" "<VSr>,wa")
 	 (match_operand:VSX_L 3 "vsx_register_operand" "<VSr>,wa")))]
   "VECTOR_MEM_VSX_P (<MODE>mode)"
@@ -1161,9 +1161,9 @@
   "VECTOR_MEM_VSX_P (<MODE>mode)"
 {
   if (INTVAL (operands[3]) == 0)
-    return \"xxpermdi %x0,%x1,%x2,1\";
+    return \"xxpermdi %x0,%x2,%x1,1\";
   else if (INTVAL (operands[3]) == 1)
-    return \"xxpermdi %x0,%x2,%x1,0\";
+    return \"xxpermdi %x0,%x1,%x2,0\";
   else
     gcc_unreachable ();
 }
