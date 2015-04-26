$NetBSD$

--- bfd/elfn32-mips.c.orig	Tue Sep  4 14:13:08 2012
+++ bfd/elfn32-mips.c
@@ -81,6 +81,8 @@ static bfd_boolean elf32_mips_grok_prstatus
   (bfd *, Elf_Internal_Note *);
 static bfd_boolean elf32_mips_grok_psinfo
   (bfd *, Elf_Internal_Note *);
+static bfd_boolean mips_elf_n32_is_local_label_name
+  (bfd *, const char *);
 static irix_compat_t elf_n32_mips_irix_compat
   (bfd *);
 
@@ -3239,6 +3241,17 @@ elf32_mips_grok_psinfo (bfd *abfd, Elf_Internal_Note *
   }
 
   return TRUE;
+}
+
+/* MIPS ELF local labels start with "$L".  */
+static bfd_boolean
+mips_elf_n32_is_local_label_name (bfd *abfd, const char *name)
+{
+  if (name[0] == '$' && name[1] == 'L')
+    return TRUE;
+
+  /* We accept the generic ELF local label syntax as well.  */
+  return _bfd_elf_is_local_label_name (abfd, name);
 }
 
 /* Depending on the target vector we generate some version of Irix
