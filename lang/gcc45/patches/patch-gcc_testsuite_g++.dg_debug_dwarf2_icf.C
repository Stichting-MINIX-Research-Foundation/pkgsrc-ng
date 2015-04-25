$NetBSD$

--- gcc/testsuite/g++.dg/debug/dwarf2/icf.C.orig	Thu Oct  8 21:00:04 2009
+++ gcc/testsuite/g++.dg/debug/dwarf2/icf.C
@@ -40,11 +40,11 @@ test2(A* a)
 
 // Verify that we get .debug_dcall and .debug_vcall tables generated
 // and that we see entries for both virtual calls. 
-// { dg-final { scan-assembler "\\.section.*\.debug_dcall" } }
+// { dg-final { scan-assembler "\\.section.*\.debug_dcall" { xfail mips-sgi-irix* } } }
 // { dg-final { scan-assembler "\\.section.*\.debug_vcall" } }
-// { dg-final { scan-assembler "New caller" } }
-// { dg-final { scan-assembler "Caller DIE offset" } }
+// { dg-final { scan-assembler "New caller" { xfail mips-sgi-irix* } } }
+// { dg-final { scan-assembler "Caller DIE offset" { xfail mips-sgi-irix* } } }
 // { dg-final { scan-assembler "Point of call" } }
-// { dg-final { scan-assembler "Callee DIE offset" } }
+// { dg-final { scan-assembler "Callee DIE offset" { xfail mips-sgi-irix* } } }
 // { dg-final { scan-assembler "0x0.*Vtable slot" } }
 // { dg-final { scan-assembler "0x1.*Vtable slot" } }
