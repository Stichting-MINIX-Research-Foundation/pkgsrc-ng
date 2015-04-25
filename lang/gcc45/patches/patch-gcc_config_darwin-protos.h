$NetBSD$

--- gcc/config/darwin-protos.h.orig	Thu Jun 24 21:06:37 2010
+++ gcc/config/darwin-protos.h
@@ -93,3 +93,4 @@ extern void darwin_asm_output_anchor (rtx symbol);
 extern bool darwin_kextabi_p (void);
 extern void darwin_override_options (void);
 extern void darwin_patch_builtins (void);
+extern void darwin_rename_builtins (void);
