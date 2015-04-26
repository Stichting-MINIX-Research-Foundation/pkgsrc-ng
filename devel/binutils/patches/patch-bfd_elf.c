$NetBSD$

--- bfd/elf.c.orig	Mon Mar 25 08:06:19 2013
+++ bfd/elf.c
@@ -8756,6 +8756,23 @@ elfcore_grok_netbsd_note (bfd *abfd, Elf_Internal_Note
 	  return TRUE;
 	}
 
+      /* On SuperH, PT_GETREGS == mach+3 and PT_GETFPREGS == mach+5.
+	 There's also old PT___GETREGS40 == mach + 1 for old reg
+	 structure which lacks GBR.  */
+
+    case bfd_arch_sh:
+      switch (note->type)
+	{
+	case NT_NETBSDCORE_FIRSTMACH+3:
+	  return elfcore_make_note_pseudosection (abfd, ".reg", note);
+
+	case NT_NETBSDCORE_FIRSTMACH+5:
+	  return elfcore_make_note_pseudosection (abfd, ".reg2", note);
+
+	default:
+	  return TRUE;
+	}
+
       /* On all other arch's, PT_GETREGS == mach+1 and
 	 PT_GETFPREGS == mach+3.  */
 
