$NetBSD$

--- bfd/archive.c.orig	Mon Mar 25 08:06:19 2013
+++ bfd/archive.c
@@ -157,6 +157,9 @@ struct ar_cache
 #define ar_maxnamelen(abfd) ((abfd)->xvec->ar_max_namelen)
 
 #define arch_eltdata(bfd) ((struct areltdata *) ((bfd)->arelt_data))
+
+static const char * normalize (bfd *, const char *);
+
 #define arch_hdr(bfd) ((struct ar_hdr *) arch_eltdata (bfd)->arch_header)
 
 /* True iff NAME designated a BSD 4.4 extended name.  */
@@ -760,7 +763,9 @@ bfd_generic_openr_next_archived_file (bfd *archive, bf
       /* Pad to an even boundary...
 	 Note that last_file->origin can be odd in the case of
 	 BSD-4.4-style element with a long odd size.  */
-      filestart += filestart % 2;
+      if (!strncmp(arch_hdr (last_file)->ar_name, "#1/", 3))
+	size += strlen(normalize(last_file, last_file->filename));
+      filestart += size % 2;
     }
 
   return _bfd_get_elt_at_filepos (archive, filestart);
@@ -2180,11 +2185,22 @@ _bfd_write_archive_contents (bfd *arch)
        current = current->archive_next)
     {
       char buffer[DEFAULT_BUFFERSIZE];
-      bfd_size_type remaining = arelt_size (current);
+      bfd_size_type saved_size = arelt_size (current);
+      bfd_size_type remaining = saved_size;
+      struct ar_hdr *hdr = arch_hdr (current);
 
       /* Write ar header.  */
       if (!_bfd_write_ar_hdr (arch, current))
-	return FALSE;
+        return FALSE;
+      /* Write filename if it is a 4.4BSD extended file, and add to size.  */
+      if (!strncmp (hdr->ar_name, "#1/", 3))
+	{
+	  const char *normal = normalize (current, current->filename);
+	  unsigned int thislen = strlen (normal);
+	  if (bfd_write (normal, 1, thislen, arch) != thislen)
+	    return FALSE;
+	  saved_size += thislen;
+	}
       if (bfd_is_thin_archive (arch))
 	continue;
       if (bfd_seek (current, (file_ptr) 0, SEEK_SET) != 0)
@@ -2457,11 +2473,19 @@ bsd_write_armap (bfd *arch,
 	{
 	  do
 	    {
+#if 1
+	      bfd_size_type size = arelt_size (current);
+	      if (!strncmp(arch_hdr (current)->ar_name, "#1/", 3))
+		size += strlen(normalize(current, current->filename));
+	      firstreal += size + sizeof (struct ar_hdr);
+	      firstreal += size % 2;
+#else
 	      struct areltdata *ared = arch_eltdata (current);
 
 	      firstreal += (ared->parsed_size + ared->extra_size
 			    + sizeof (struct ar_hdr));
 	      firstreal += firstreal % 2;
+#endif
 	      current = current->archive_next;
 	    }
 	  while (current != map[count].u.abfd);
