$NetBSD$

--- gcc/config/rx/rx.c.orig	Wed Mar 16 11:47:59 2011
+++ gcc/config/rx/rx.c
@@ -2158,10 +2158,10 @@ rx_expand_builtin (tree exp,
       if (! valid_psw_flag (op, "clrpsw"))
 	return NULL_RTX;
       return rx_expand_void_builtin_1_arg (op, gen_clrpsw, false);
+    case RX_BUILTIN_SETPSW:  
       if (! valid_psw_flag (op, "setpsw"))
 	return NULL_RTX;
       return rx_expand_void_builtin_1_arg (op, gen_setpsw, false);
-    case RX_BUILTIN_SETPSW:  
     case RX_BUILTIN_INT:     return rx_expand_void_builtin_1_arg
 	(op, gen_int, false);
     case RX_BUILTIN_MACHI:   return rx_expand_builtin_mac (exp, gen_machi);
