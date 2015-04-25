$NetBSD$

--- gcc/config/vax/elf.h.orig	Wed Apr  1 17:00:00 2009
+++ gcc/config/vax/elf.h
@@ -109,5 +109,5 @@ along with GCC; see the file COPYING3.  If not see
     fputs (integer_asm_op (SIZE, FALSE), FILE);		\
     fprintf (FILE, "%%pcrel%d(", SIZE * 8);		\
     assemble_name (FILE, LABEL);			\
-    fputc (')', FILE);					\
+    fprintf (FILE, "%+d)", SIZE);			\
   } while (0)
