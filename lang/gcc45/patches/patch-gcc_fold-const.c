$NetBSD$

--- gcc/fold-const.c.orig	Mon Apr 18 14:02:22 2011
+++ gcc/fold-const.c
@@ -2784,8 +2784,6 @@ fold_convert_loc (location_t loc, tree type, tree arg)
 
     case VOID_TYPE:
       tem = fold_ignored_result (arg);
-      if (TREE_CODE (tem) == MODIFY_EXPR)
-	goto fold_convert_exit;
       return fold_build1_loc (loc, NOP_EXPR, type, tem);
 
     default:
