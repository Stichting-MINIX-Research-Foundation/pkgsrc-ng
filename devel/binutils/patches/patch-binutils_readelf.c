$NetBSD$

--- binutils/readelf.c.orig	Mon Mar 25 08:06:21 2013
+++ binutils/readelf.c
@@ -3801,7 +3801,7 @@ process_program_headers (FILE * file)
       if (elf_header.e_phnum > 1)
 	printf (_("\nProgram Headers:\n"));
       else
-	printf (_("\nProgram Headers:\n"));
+	printf (_("\nProgram Header:\n"));
 
       if (is_32bit_elf)
 	printf
@@ -6974,6 +6974,11 @@ decode_arm_unwind (struct arm_unw_aux_info *  aux,
 
       remaining = 4;
     }
+  else
+    {
+      addr.section = SHN_UNDEF;
+      addr.offset = 0;
+    }
 
   if ((word & 0x80000000) == 0)
     {
@@ -12665,6 +12670,38 @@ get_gnu_elf_note_type (unsigned e_type)
   return buff;
 }
 
+static int 
+process_netbsd_elf_note (Elf_Internal_Note * pnote)
+{
+  unsigned int version;
+
+  switch (pnote->type)
+    {
+    case NT_NETBSD_IDENT:
+      version = byte_get((unsigned char *)pnote->descdata, sizeof(version));
+      if ((version / 10000) % 100)
+        printf ("  NetBSD\t0x%08lx\tIDENT %u (%u.%u%s%c)\n", pnote->descsz,
+		version, version / 100000000, (version / 1000000) % 100,
+		(version / 10000) % 100 > 26 ? "Z" : "",
+		'A' + (version / 10000) % 26); 
+      else
+	printf ("  NetBSD\t0x%08lx\tIDENT %u (%u.%u.%u)\n", pnote->descsz,
+	        version, version / 100000000, (version / 1000000) % 100,
+		(version / 100) % 100); 
+      return 1;
+    case NT_NETBSD_MARCH:
+      printf ("  NetBSD\t0x%08lx\tMARCH <%s>\n", pnote->descsz,
+	      pnote->descdata);
+      return 1;
+    default:
+      break;
+    }
+
+  printf ("  NetBSD\t0x%08lx\tUnknown note type: (0x%08lx)\n", pnote->descsz,
+	  pnote->type);
+  return 1;
+}
+
 static int
 print_gnu_note (Elf_Internal_Note *pnote)
 {
@@ -12765,6 +12802,23 @@ get_netbsd_elfcore_note_type (unsigned e_type)
 	}
       break;
 
+    /* On SuperH, PT_GETREGS == mach+3 and PT_GETFPREGS == mach+5.
+       There's also old PT___GETREGS40 == mach + 1 for old reg
+       structure which lacks GBR.  */
+    case EM_SH:
+      switch (e_type)
+	{
+	case NT_NETBSDCORE_FIRSTMACH + 1:
+	  return _("PT___GETREGS40 (old reg structure)");
+	case NT_NETBSDCORE_FIRSTMACH + 3:
+	  return _("PT_GETREGS (reg structure)");
+	case NT_NETBSDCORE_FIRSTMACH + 5:
+	  return _("PT_GETFPREGS (fpreg structure)");
+	default:
+	  break;
+	}
+      break;
+
     /* On all other arch's, PT_GETREGS == mach+1 and
        PT_GETFPREGS == mach+3.  */
     default:
@@ -12970,6 +13024,10 @@ process_note (Elf_Internal_Note * pnote)
   else if (const_strneq (pnote->namedata, "GNU"))
     /* GNU-specific object file notes.  */
     nt = get_gnu_elf_note_type (pnote->type);
+
+  else if (const_strneq (pnote->namedata, "NetBSD"))
+    /* NetBSD-specific core file notes.  */
+    return process_netbsd_elf_note (pnote);
 
   else if (const_strneq (pnote->namedata, "NetBSD-CORE"))
     /* NetBSD-specific core file notes.  */
