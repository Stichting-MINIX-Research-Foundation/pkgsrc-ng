$NetBSD$

--- gcc/testsuite/gcc.c-torture/execute/960321-1.x.orig	Mon Jun  7 21:15:05 2010
+++ gcc/testsuite/gcc.c-torture/execute/960321-1.x
@@ -1,15 +0,0 @@
-# This test fails to link on 64-bit Solaris 2/x86 due to a Sun as bug.
-if { [istarget "i?86-*-solaris2*"]
-     && ! [check_effective_target_ilp32]
-     && ! [check_effective_target_gas] } { 
-    set torture_eval_before_compile {
-        global compiler_conditional_xfail_data
-        set compiler_conditional_xfail_data {
-            "64-bit Sun as bug" \
-                { "i?86-*-solaris2*" } \
-                { "-O[1-3s]" } \
-                { "" }
-       }
-    }
-}
-return 0
