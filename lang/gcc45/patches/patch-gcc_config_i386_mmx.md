$NetBSD$

--- gcc/config/i386/mmx.md.orig	Wed Dec 30 11:07:12 2009
+++ gcc/config/i386/mmx.md
@@ -63,6 +63,7 @@
   DONE;
 })
 
+;; movd instead of movq is required to handle broken assemblers.
 (define_insn "*mov<mode>_internal_rex64"
   [(set (match_operand:MMXMODEI8 0 "nonimmediate_operand"
 				"=rm,r,!?y,!?y ,m  ,!y,*Y2,x,x ,m,r,Yi")
@@ -81,8 +82,8 @@
     %vpxor\t%0, %d0
     %vmovq\t{%1, %0|%0, %1}
     %vmovq\t{%1, %0|%0, %1}
-    %vmovq\t{%1, %0|%0, %1}
-    %vmovq\t{%1, %0|%0, %1}"
+    %vmovd\t{%1, %0|%0, %1}
+    %vmovd\t{%1, %0|%0, %1}"
   [(set_attr "type" "imov,imov,mmx,mmxmov,mmxmov,ssecvt,ssecvt,sselog1,ssemov,ssemov,ssemov,ssemov")
    (set_attr "unit" "*,*,*,*,*,mmx,mmx,*,*,*,*,*")
    (set_attr "prefix_rep" "*,*,*,*,*,1,1,*,1,*,*,*")
@@ -192,6 +193,7 @@
        (const_string "orig")))
    (set_attr "mode" "DI,DI,DI,DI,DI,DI,DI,V4SF,V4SF,V2SF,V2SF,DI,DI")])
 
+;; movd instead of movq is required to handle broken assemblers.
 (define_insn "*movv2sf_internal_rex64"
   [(set (match_operand:V2SF 0 "nonimmediate_operand"
 				"=rm,r ,!?y,!?y ,m ,!y,*Y2,x,x,x,m,r,Yi")
