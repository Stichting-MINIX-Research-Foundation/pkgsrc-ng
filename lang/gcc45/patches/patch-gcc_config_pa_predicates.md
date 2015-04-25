$NetBSD$

--- gcc/config/pa/predicates.md.orig	Sat Jul  3 22:46:51 2010
+++ gcc/config/pa/predicates.md
@@ -411,15 +411,19 @@
 
 ;; True iff depi can be used to compute (reg | OP).
 
-(define_predicate "ior_operand"
-  (match_code "const_int")
-{
-  return (GET_CODE (op) == CONST_INT && ior_mask_p (INTVAL (op)));
-})
+(define_predicate "cint_ior_operand"
+  (and (match_code "const_int")
+       (match_test "ior_mask_p (INTVAL (op))")))
 
-;; True iff OP is a CONST_INT of the forms 0...0xxxx or
-;; 0...01...1xxxx. Such values can be the left hand side x in (x <<
-;; r), using the zvdepi instruction.
+;; True iff OP can be used to compute (reg | OP).
+
+(define_predicate "reg_or_cint_ior_operand"
+  (ior (match_operand 0 "register_operand")
+       (match_operand 0 "cint_ior_operand")))
+
+;; True iff OP is a CONST_INT of the forms 0...0xxxx, 0...01...1xxxx,
+;; or 1...1xxxx. Such values can be the left hand side x in (x << r),
+;; using the zvdepi instruction.
 
 (define_predicate "lhs_lshift_cint_operand"
   (match_code "const_int")
