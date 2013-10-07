$NetBSD$

--- bfd/aoutx.h.orig	Tue May  1 16:07:33 2012
+++ bfd/aoutx.h
@@ -762,7 +762,7 @@ NAME (aout, machine_type) (enum bfd_architecture arch,
       break;
 
     case bfd_arch_arm:
-      if (machine == 0)
+      if (machine == 0 || machine == 5)
 	arch_flags = M_ARM;
       break;
 
