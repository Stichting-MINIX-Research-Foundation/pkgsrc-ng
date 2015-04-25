$NetBSD$

--- gcc/function.c.orig	Mon Aug 16 20:18:08 2010
+++ gcc/function.c
@@ -1,7 +1,7 @@
 /* Expands front end tree to back end RTL for GCC.
    Copyright (C) 1987, 1988, 1989, 1991, 1992, 1993, 1994, 1995, 1996, 1997,
    1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
-   2010  Free Software Foundation, Inc.
+   2010, 2012  Free Software Foundation, Inc.
 
 This file is part of GCC.
 
@@ -1643,7 +1643,7 @@ instantiate_virtual_regs_in_insn (rtx insn)
       if (!check_asm_operands (PATTERN (insn)))
 	{
 	  error_for_asm (insn, "impossible constraint in %<asm%>");
-	  delete_insn (insn);
+	  delete_insn_and_edges (insn);
 	}
     }
   else
