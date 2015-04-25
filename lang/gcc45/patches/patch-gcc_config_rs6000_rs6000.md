$NetBSD$

--- gcc/config/rs6000/rs6000.md.orig	Wed Nov  3 13:55:26 2010
+++ gcc/config/rs6000/rs6000.md
@@ -2483,8 +2483,19 @@
   if (GET_CODE (addr1) == PLUS)
     {
       emit_insn (gen_add3_insn (op2, XEXP (addr1, 0), GEN_INT (4)));
-      addr2 = gen_rtx_PLUS (Pmode, op2, XEXP (addr1, 1));
+      if (TARGET_AVOID_XFORM)
+	{
+	  emit_insn (gen_add3_insn (op2, XEXP (addr1, 1), op2));
+	  addr2 = op2;
+	}
+      else
+	addr2 = gen_rtx_PLUS (Pmode, op2, XEXP (addr1, 1));
     }
+  else if (TARGET_AVOID_XFORM)
+    {
+      emit_insn (gen_add3_insn (op2, addr1, GEN_INT (4)));
+      addr2 = op2;
+    }
   else
     {
       emit_move_insn (op2, GEN_INT (4));
@@ -2533,8 +2544,19 @@
   if (GET_CODE (addr1) == PLUS)
     {
       emit_insn (gen_add3_insn (op2, XEXP (addr1, 0), GEN_INT (4)));
-      addr2 = gen_rtx_PLUS (Pmode, op2, XEXP (addr1, 1));
+      if (TARGET_AVOID_XFORM)
+	{
+	  emit_insn (gen_add3_insn (op2, XEXP (addr1, 1), op2));
+	  addr2 = op2;
+	}
+      else
+	addr2 = gen_rtx_PLUS (Pmode, op2, XEXP (addr1, 1));
     }
+  else if (TARGET_AVOID_XFORM)
+    {
+      emit_insn (gen_add3_insn (op2, addr1, GEN_INT (4)));
+      addr2 = op2;
+    }
   else
     {
       emit_move_insn (op2, GEN_INT (4));
@@ -2614,8 +2636,19 @@
   if (GET_CODE (addr1) == PLUS)
     {
       emit_insn (gen_add3_insn (op2, XEXP (addr1, 0), GEN_INT (4)));
-      addr2 = gen_rtx_PLUS (SImode, op2, XEXP (addr1, 1));
+      if (TARGET_AVOID_XFORM)
+	{
+	  emit_insn (gen_add3_insn (op2, XEXP (addr1, 1), op2));
+	  addr2 = op2;
+	}
+      else
+	addr2 = gen_rtx_PLUS (SImode, op2, XEXP (addr1, 1));
     }
+  else if (TARGET_AVOID_XFORM)
+    {
+      emit_insn (gen_add3_insn (op2, addr1, GEN_INT (4)));
+      addr2 = op2;
+    }
   else
     {
       emit_move_insn (op2, GEN_INT (4));
@@ -2659,8 +2692,19 @@
   if (GET_CODE (addr1) == PLUS)
     {
       emit_insn (gen_add3_insn (op2, XEXP (addr1, 0), GEN_INT (4)));
-      addr2 = gen_rtx_PLUS (SImode, op2, XEXP (addr1, 1));
+      if (TARGET_AVOID_XFORM)
+	{
+	  emit_insn (gen_add3_insn (op2, XEXP (addr1, 1), op2));
+	  addr2 = op2;
+	}
+      else
+	addr2 = gen_rtx_PLUS (SImode, op2, XEXP (addr1, 1));
     }
+  else if (TARGET_AVOID_XFORM)
+    {
+      emit_insn (gen_add3_insn (op2, addr1, GEN_INT (4)));
+      addr2 = op2;
+    }
   else
     {
       emit_move_insn (op2, GEN_INT (4));
@@ -12473,7 +12517,11 @@
   [(set (match_operand 0 "memory_operand" "=m")
         (unspec [(const_int 0)] UNSPEC_PROBE_STACK))]
   ""
-  "{st%U0%X0|stw%U0%X0} 0,%0"
+  "*
+{
+  operands[1] = gen_rtx_REG (Pmode, 0);
+  return \"{st%U0%X0|stw%U0%X0} %1,%0\";
+}"
   [(set_attr "type" "store")
    (set_attr "length" "4")])
 
