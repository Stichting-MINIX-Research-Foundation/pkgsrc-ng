$NetBSD$

--- gcc/config/sparc/sol2-64.h.orig	Tue Mar  2 23:35:12 2010
+++ gcc/config/sparc/sol2-64.h
@@ -1,7 +1,7 @@
 /* Definitions of target machine for GCC, for bi-arch SPARC
    running Solaris 2, defaulting to 64-bit code generation.
 
-   Copyright (C) 1999, 2010 Free Software Foundation, Inc.
+   Copyright (C) 1999, 2010, 2011 Free Software Foundation, Inc.
 
 This file is part of GCC.
 
@@ -19,7 +19,4 @@ You should have received a copy of the GNU General Pub
 along with GCC; see the file COPYING3.  If not see
 <http://www.gnu.org/licenses/>.  */
 
-#undef TARGET_DEFAULT
-#define TARGET_DEFAULT \
-  (MASK_V9 + MASK_PTR64 + MASK_64BIT /* + MASK_HARD_QUAD */ + \
-   MASK_STACK_BIAS + MASK_APP_REGS + MASK_FPU + MASK_LONG_DOUBLE_128)
+#define TARGET_64BIT_DEFAULT 1
