$NetBSD$

--- gcc/config/arm/arm.md.orig	Tue Apr 12 13:52:46 2011
+++ gcc/config/arm/arm.md
@@ -3134,7 +3134,7 @@
     bool need_else;
 
     if (which_alternative != 0 || operands[3] != const0_rtx
-        || (code != PLUS && code != MINUS && code != IOR && code != XOR))
+        || (code != PLUS && code != IOR && code != XOR))
       need_else = true;
     else
       need_else = false;
@@ -3189,7 +3189,7 @@
 )
 
 (define_insn "arm_ashldi3_1bit"
-  [(set (match_operand:DI            0 "s_register_operand" "=&r,r")
+  [(set (match_operand:DI            0 "s_register_operand" "=r,&r")
         (ashift:DI (match_operand:DI 1 "s_register_operand" "0,r")
                    (const_int 1)))
    (clobber (reg:CC CC_REGNUM))]
@@ -3248,7 +3248,7 @@
 )
 
 (define_insn "arm_ashrdi3_1bit"
-  [(set (match_operand:DI              0 "s_register_operand" "=&r,r")
+  [(set (match_operand:DI              0 "s_register_operand" "=r,&r")
         (ashiftrt:DI (match_operand:DI 1 "s_register_operand" "0,r")
                      (const_int 1)))
    (clobber (reg:CC CC_REGNUM))]
@@ -3304,7 +3304,7 @@
 )
 
 (define_insn "arm_lshrdi3_1bit"
-  [(set (match_operand:DI              0 "s_register_operand" "=&r,r")
+  [(set (match_operand:DI              0 "s_register_operand" "=r,&r")
         (lshiftrt:DI (match_operand:DI 1 "s_register_operand" "0,r")
                      (const_int 1)))
    (clobber (reg:CC CC_REGNUM))]
@@ -7994,7 +7994,7 @@
 	(not:SI (match_operator:SI 1 "arm_comparison_operator"
 		 [(match_operand 2 "cc_register" "") (const_int 0)])))]
   "TARGET_ARM"
-  "mov%D1\\t%0, #0\;mvn%d1\\t%0, #1"
+  "mvn%D1\\t%0, #0\;mvn%d1\\t%0, #1"
   [(set_attr "conds" "use")
    (set_attr "length" "8")]
 )
