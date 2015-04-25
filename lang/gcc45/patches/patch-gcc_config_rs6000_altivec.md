$NetBSD$

--- gcc/config/rs6000/altivec.md.orig	Fri Feb  4 16:31:48 2011
+++ gcc/config/rs6000/altivec.md
@@ -497,7 +497,7 @@
   [(set (match_operand:VM 0 "altivec_register_operand" "=v")
 	(if_then_else:VM
 	 (ne:CC (match_operand:VM 1 "altivec_register_operand" "v")
-		(const_int 0))
+		(match_operand:VM 4 "zero_constant" ""))
 	 (match_operand:VM 2 "altivec_register_operand" "v")
 	 (match_operand:VM 3 "altivec_register_operand" "v")))]
   "VECTOR_MEM_ALTIVEC_P (<MODE>mode)"
@@ -508,7 +508,7 @@
   [(set (match_operand:VM 0 "altivec_register_operand" "=v")
 	(if_then_else:VM
 	 (ne:CCUNS (match_operand:VM 1 "altivec_register_operand" "v")
-		   (const_int 0))
+		   (match_operand:VM 4 "zero_constant" ""))
 	 (match_operand:VM 2 "altivec_register_operand" "v")
 	 (match_operand:VM 3 "altivec_register_operand" "v")))]
   "VECTOR_MEM_ALTIVEC_P (<MODE>mode)"
@@ -2396,8 +2396,8 @@
 
 (define_insn "altivec_stvlx"
   [(parallel
-    [(set (match_operand:V4SI 0 "memory_operand" "=Z")
-	  (match_operand:V4SI 1 "register_operand" "v"))
+    [(set (match_operand:V16QI 0 "memory_operand" "=Z")
+	  (match_operand:V16QI 1 "register_operand" "v"))
      (unspec [(const_int 0)] UNSPEC_STVLX)])]
   "TARGET_ALTIVEC && rs6000_cpu == PROCESSOR_CELL"
   "stvlx %1,%y0"
@@ -2405,8 +2405,8 @@
 
 (define_insn "altivec_stvlxl"
   [(parallel
-    [(set (match_operand:V4SI 0 "memory_operand" "=Z")
-	  (match_operand:V4SI 1 "register_operand" "v"))
+    [(set (match_operand:V16QI 0 "memory_operand" "=Z")
+	  (match_operand:V16QI 1 "register_operand" "v"))
      (unspec [(const_int 0)] UNSPEC_STVLXL)])]
   "TARGET_ALTIVEC && rs6000_cpu == PROCESSOR_CELL"
   "stvlxl %1,%y0"
@@ -2414,8 +2414,8 @@
 
 (define_insn "altivec_stvrx"
   [(parallel
-    [(set (match_operand:V4SI 0 "memory_operand" "=Z")
-	  (match_operand:V4SI 1 "register_operand" "v"))
+    [(set (match_operand:V16QI 0 "memory_operand" "=Z")
+	  (match_operand:V16QI 1 "register_operand" "v"))
      (unspec [(const_int 0)] UNSPEC_STVRX)])]
   "TARGET_ALTIVEC && rs6000_cpu == PROCESSOR_CELL"
   "stvrx %1,%y0"
@@ -2423,8 +2423,8 @@
 
 (define_insn "altivec_stvrxl"
   [(parallel
-    [(set (match_operand:V4SI 0 "memory_operand" "=Z")
-	  (match_operand:V4SI 1 "register_operand" "v"))
+    [(set (match_operand:V16QI 0 "memory_operand" "=Z")
+	  (match_operand:V16QI 1 "register_operand" "v"))
      (unspec [(const_int 0)] UNSPEC_STVRXL)])]
   "TARGET_ALTIVEC && rs6000_cpu == PROCESSOR_CELL"
   "stvrxl %1,%y0"
