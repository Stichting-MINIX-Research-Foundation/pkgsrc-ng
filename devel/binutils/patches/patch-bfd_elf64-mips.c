$NetBSD$

--- bfd/elf64-mips.c.orig	Tue Sep  4 14:13:07 2012
+++ bfd/elf64-mips.c
@@ -123,6 +123,8 @@ static bfd_reloc_status_type mips_elf64_final_gp
   (bfd *, asymbol *, bfd_boolean, char **, bfd_vma *);
 static bfd_boolean mips_elf64_object_p
   (bfd *);
+static bfd_boolean mips_elf64_is_local_label_name
+  (bfd *, const char *);
 static irix_compat_t elf64_mips_irix_compat
   (bfd *);
 static bfd_boolean elf64_mips_grok_prstatus
@@ -3917,7 +3919,18 @@ mips_elf64_object_p (bfd *abfd)
   bfd_default_set_arch_mach (abfd, bfd_arch_mips, mach);
   return TRUE;
 }
+
+/* MIPS ELF local labels start with "$L".  */
+static bfd_boolean
+mips_elf64_is_local_label_name (bfd *abfd, const char *name)
+{
+  if (name[0] == '$' && name[1] == 'L')
+    return TRUE;
 
+  /* We accept the generic ELF local label syntax as well.  */
+  return _bfd_elf_is_local_label_name (abfd, name);
+}
+
 /* Depending on the target vector we generate some version of Irix
    executables or "normal" MIPS ELF ABI executables.  */
 static irix_compat_t
