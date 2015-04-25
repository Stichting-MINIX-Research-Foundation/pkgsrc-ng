$NetBSD$

--- gcc/config/i386/athlon.md.orig	Tue Apr 21 19:03:23 2009
+++ gcc/config/i386/athlon.md
@@ -798,7 +798,7 @@
 			 "athlon-direct,athlon-fploadk8,athlon-fadd")
 (define_insn_reservation "athlon_ssecomi" 4
 			 (and (eq_attr "cpu" "athlon,k8,generic64")
-			      (eq_attr "type" "ssecmp"))
+			      (eq_attr "type" "ssecomi"))
 			 "athlon-vector,athlon-fpsched,athlon-fadd")
 (define_insn_reservation "athlon_ssecomi_amdfam10" 3
 			 (and (eq_attr "cpu" "amdfam10")
