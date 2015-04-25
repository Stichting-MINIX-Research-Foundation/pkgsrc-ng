$NetBSD$

--- gcc/config/m68k/m68k.md.orig	Wed Dec 30 23:03:46 2009
+++ gcc/config/m68k/m68k.md
@@ -3116,16 +3116,33 @@
 ;; We need a separate DEFINE_EXPAND for u?mulsidi3 to be able to use the
 ;; proper matching constraint.  This is because the matching is between
 ;; the high-numbered word of the DImode operand[0] and operand[1].
+;;
+;; Note: life_analysis() does not keep track of the individual halves of the
+;; DImode register.  To prevent spurious liveness before the u?mulsidi3 insn
+;; (which causes "uninitialized variable" warnings), we explicitly clobber
+;; the DImode register.
 (define_expand "umulsidi3"
-  [(parallel
-    [(set (subreg:SI (match_operand:DI 0 "register_operand" "") 4)
-	  (mult:SI (match_operand:SI 1 "register_operand" "")
-		   (match_operand:SI 2 "register_operand" "")))
+  [(set (match_operand:DI 0 "register_operand" "")
+	(mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" ""))
+		 (zero_extend:DI (match_operand:SI 2 "register_operand" ""))))]
+  "TARGET_68020 && !TUNE_68060 && !TARGET_COLDFIRE"
+  "")
+
+(define_insn_and_split "*umulsidi3_split"
+  [(set (match_operand:DI 0 "register_operand" "")
+	(mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" ""))
+		 (zero_extend:DI (match_operand:SI 2 "register_operand" ""))))]
+  "TARGET_68020 && !TUNE_68060 && !TARGET_COLDFIRE"
+  "#"
+  "TARGET_68020 && !TUNE_68060 && !TARGET_COLDFIRE"
+  [(clobber (match_dup 0))
+   (parallel
+    [(set (subreg:SI (match_dup 0) 4)
+	  (mult:SI (match_dup 1) (match_dup 2)))
      (set (subreg:SI (match_dup 0) 0)
 	  (truncate:SI (lshiftrt:DI (mult:DI (zero_extend:DI (match_dup 1))
 					     (zero_extend:DI (match_dup 2)))
 				    (const_int 32))))])]
-  "TARGET_68020 && !TUNE_68060 && !TARGET_COLDFIRE"
   "")
 
 (define_insn ""
@@ -3156,15 +3173,27 @@
   "mulu%.l %2,%3:%0")
 
 (define_expand "mulsidi3"
-  [(parallel
-    [(set (subreg:SI (match_operand:DI 0 "register_operand" "") 4)
-	  (mult:SI (match_operand:SI 1 "register_operand" "")
-		   (match_operand:SI 2 "register_operand" "")))
+  [(set (match_operand:DI 0 "register_operand" "")
+	(mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" ""))
+		 (sign_extend:DI (match_operand:SI 2 "register_operand" ""))))]
+  "TARGET_68020 && !TUNE_68060 && !TARGET_COLDFIRE"
+  "")
+
+(define_insn_and_split "*mulsidi3_split"
+  [(set (match_operand:DI 0 "register_operand" "")
+	(mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" ""))
+		 (sign_extend:DI (match_operand:SI 2 "register_operand" ""))))]
+  "TARGET_68020 && !TUNE_68060 && !TARGET_COLDFIRE"
+  "#"
+  "TARGET_68020 && !TUNE_68060 && !TARGET_COLDFIRE"
+  [(clobber (match_dup 0))
+   (parallel
+    [(set (subreg:SI (match_dup 0) 4)
+	  (mult:SI (match_dup 1) (match_dup 2)))
      (set (subreg:SI (match_dup 0) 0)
 	  (truncate:SI (lshiftrt:DI (mult:DI (sign_extend:DI (match_dup 1))
 					     (sign_extend:DI (match_dup 2)))
 				    (const_int 32))))])]
-  "TARGET_68020 && !TUNE_68060 && !TARGET_COLDFIRE"
   "")
 
 (define_insn ""
