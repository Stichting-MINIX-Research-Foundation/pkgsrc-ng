$NetBSD$

--- gcc/config/arm/neon.md.orig	Mon Jul  5 12:45:19 2010
+++ gcc/config/arm/neon.md
@@ -680,7 +680,7 @@
           (match_operand:SI 2 "immediate_operand" "i")))]
   "TARGET_NEON"
 {
-  int elt = ffs ((int) INTVAL (operands[2]) - 1);
+  int elt = ffs ((int) INTVAL (operands[2])) - 1;
   if (BYTES_BIG_ENDIAN)
     elt = GET_MODE_NUNITS (<MODE>mode) - 1 - elt;
   operands[2] = GEN_INT (elt);
@@ -3895,13 +3895,14 @@
 
 (define_insn "neon_vtrn<mode>_internal"
   [(set (match_operand:VDQW 0 "s_register_operand" "=w")
-	(unspec:VDQW [(match_operand:VDQW 1 "s_register_operand" "0")]
-		     UNSPEC_VTRN1))
-   (set (match_operand:VDQW 2 "s_register_operand" "=w")
-        (unspec:VDQW [(match_operand:VDQW 3 "s_register_operand" "2")]
-		     UNSPEC_VTRN2))]
+        (unspec:VDQW [(match_operand:VDQW 1 "s_register_operand" "0")
+                      (match_operand:VDQW 2 "s_register_operand" "w")]
+                     UNSPEC_VTRN1))
+   (set (match_operand:VDQW 3 "s_register_operand" "=2")
+         (unspec:VDQW [(match_dup 1) (match_dup 2)]
+                     UNSPEC_VTRN2))]
   "TARGET_NEON"
-  "vtrn.<V_sz_elem>\t%<V_reg>0, %<V_reg>2"
+  "vtrn.<V_sz_elem>\t%<V_reg>0, %<V_reg>3"
   [(set (attr "neon_type")
       (if_then_else (ne (symbol_ref "<Is_d_reg>") (const_int 0))
                     (const_string "neon_bp_simple")
@@ -3921,13 +3922,14 @@
 
 (define_insn "neon_vzip<mode>_internal"
   [(set (match_operand:VDQW 0 "s_register_operand" "=w")
-	(unspec:VDQW [(match_operand:VDQW 1 "s_register_operand" "0")]
-		     UNSPEC_VZIP1))
-   (set (match_operand:VDQW 2 "s_register_operand" "=w")
-        (unspec:VDQW [(match_operand:VDQW 3 "s_register_operand" "2")]
-		     UNSPEC_VZIP2))]
+        (unspec:VDQW [(match_operand:VDQW 1 "s_register_operand" "0")
+                      (match_operand:VDQW 2 "s_register_operand" "w")]
+                     UNSPEC_VZIP1))
+   (set (match_operand:VDQW 3 "s_register_operand" "=2")
+        (unspec:VDQW [(match_dup 1) (match_dup 2)]
+                     UNSPEC_VZIP2))]
   "TARGET_NEON"
-  "vzip.<V_sz_elem>\t%<V_reg>0, %<V_reg>2"
+  "vzip.<V_sz_elem>\t%<V_reg>0, %<V_reg>3"
   [(set (attr "neon_type")
       (if_then_else (ne (symbol_ref "<Is_d_reg>") (const_int 0))
                     (const_string "neon_bp_simple")
@@ -3947,13 +3949,14 @@
 
 (define_insn "neon_vuzp<mode>_internal"
   [(set (match_operand:VDQW 0 "s_register_operand" "=w")
-	(unspec:VDQW [(match_operand:VDQW 1 "s_register_operand" "0")]
+        (unspec:VDQW [(match_operand:VDQW 1 "s_register_operand" "0")
+                      (match_operand:VDQW 2 "s_register_operand" "w")]
                      UNSPEC_VUZP1))
-   (set (match_operand:VDQW 2 "s_register_operand" "=w")
-        (unspec:VDQW [(match_operand:VDQW 3 "s_register_operand" "2")]
-		     UNSPEC_VUZP2))]
+   (set (match_operand:VDQW 3 "s_register_operand" "=2")
+        (unspec:VDQW [(match_dup 1) (match_dup 2)]
+                     UNSPEC_VUZP2))]
   "TARGET_NEON"
-  "vuzp.<V_sz_elem>\t%<V_reg>0, %<V_reg>2"
+  "vuzp.<V_sz_elem>\t%<V_reg>0, %<V_reg>3"
   [(set (attr "neon_type")
       (if_then_else (ne (symbol_ref "<Is_d_reg>") (const_int 0))
                     (const_string "neon_bp_simple")
