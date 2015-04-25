$NetBSD$

--- gcc/recog.c.orig	Fri Apr  2 19:54:46 2010
+++ gcc/recog.c
@@ -2991,6 +2991,7 @@ peep2_find_free_register (int from, int to, const char
   static int search_ofs;
   enum reg_class cl;
   HARD_REG_SET live;
+  df_ref *def_rec;
   int i;
 
   gcc_assert (from < MAX_INSNS_PER_PEEP2 + 1);
@@ -3008,13 +3009,15 @@ peep2_find_free_register (int from, int to, const char
 
   while (from != to)
     {
-      HARD_REG_SET this_live;
+      gcc_assert (peep2_insn_data[from].insn != NULL_RTX);
 
+      /* Don't use registers set or clobbered by the insn.  */
+      for (def_rec = DF_INSN_DEFS (peep2_insn_data[from].insn);
+	   *def_rec; def_rec++)
+	SET_HARD_REG_BIT (live, DF_REF_REGNO (*def_rec));
+
       if (++from >= MAX_INSNS_PER_PEEP2 + 1)
 	from = 0;
-      gcc_assert (peep2_insn_data[from].insn != NULL_RTX);
-      REG_SET_TO_HARD_REG_SET (this_live, peep2_insn_data[from].live_before);
-      IOR_HARD_REG_SET (live, this_live);
     }
 
   cl = (class_str[0] == 'r' ? GENERAL_REGS
