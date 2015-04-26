$NetBSD$

--- gas/config/tc-arm.c.orig	Mon Mar 25 08:06:21 2013
+++ gas/config/tc-arm.c
@@ -17290,12 +17290,16 @@ check_it_blocks_finished (void)
   asection *sect;
 
   for (sect = stdoutput->sections; sect != NULL; sect = sect->next)
-    if (seg_info (sect)->tc_segment_info_data.current_it.state
-	== MANUAL_IT_BLOCK)
-      {
-	as_warn (_("section '%s' finished with an open IT block."),
-		 sect->name);
-      }
+    {
+      segment_info_type *seginfo = seg_info (sect);
+
+      if (seginfo && seginfo->tc_segment_info_data.current_it.state
+	  == MANUAL_IT_BLOCK)
+        {
+	  as_warn (_("section '%s' finished with an open IT block."),
+		   sect->name);
+        }
+    }
 #else
   if (now_it.state == MANUAL_IT_BLOCK)
     as_warn (_("file finished with an open IT block."));
