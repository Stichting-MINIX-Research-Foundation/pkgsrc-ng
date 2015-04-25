$NetBSD$

--- gcc/config/sparc/sparc-protos.h.orig	Fri Apr  2 19:54:46 2010
+++ gcc/config/sparc/sparc-protos.h
@@ -48,6 +48,7 @@ extern bool sparc_can_use_return_insn_p (void);
 extern int check_pic (int);
 extern int short_branch (int, int);
 extern void sparc_profile_hook (int);
+extern void sparc_optimization_options (int, int);
 extern void sparc_override_options (void);
 extern void sparc_output_scratch_registers (FILE *);
 
