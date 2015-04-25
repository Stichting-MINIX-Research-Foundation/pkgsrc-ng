$NetBSD$

--- gcc/config/pa/pa.c.orig	Sat Apr 16 18:09:58 2011
+++ gcc/config/pa/pa.c
@@ -990,9 +990,9 @@ hppa_legitimize_address (rtx x, rtx oldx ATTRIBUTE_UNU
 	  || GET_CODE (XEXP (x, 0)) == REG))
     {
       rtx int_part, ptr_reg;
-      int newoffset;
-      int offset = INTVAL (XEXP (x, 1));
-      int mask;
+      HOST_WIDE_INT newoffset;
+      HOST_WIDE_INT offset = INTVAL (XEXP (x, 1));
+      HOST_WIDE_INT mask;
 
       mask = (GET_MODE_CLASS (mode) == MODE_FLOAT
 	      ? (INT14_OK_STRICT ? 0x3fff : 0x1f) : 0x3fff);
@@ -1046,7 +1046,7 @@ hppa_legitimize_address (rtx x, rtx oldx ATTRIBUTE_UNU
 	  || GET_CODE (XEXP (x, 1)) == SUBREG)
       && GET_CODE (XEXP (x, 1)) != CONST)
     {
-      int val = INTVAL (XEXP (XEXP (x, 0), 1));
+      HOST_WIDE_INT val = INTVAL (XEXP (XEXP (x, 0), 1));
       rtx reg1, reg2;
 
       reg1 = XEXP (x, 1);
@@ -1125,7 +1125,7 @@ hppa_legitimize_address (rtx x, rtx oldx ATTRIBUTE_UNU
 	  && INTVAL (XEXP (idx, 1)) % INTVAL (XEXP (XEXP (idx, 0), 1)) == 0)
 	{
 	  /* Divide the CONST_INT by the scale factor, then add it to A.  */
-	  int val = INTVAL (XEXP (idx, 1));
+	  HOST_WIDE_INT val = INTVAL (XEXP (idx, 1));
 
 	  val /= INTVAL (XEXP (XEXP (idx, 0), 1));
 	  reg1 = XEXP (XEXP (idx, 0), 0);
@@ -1148,7 +1148,7 @@ hppa_legitimize_address (rtx x, rtx oldx ATTRIBUTE_UNU
 	  && INTVAL (XEXP (idx, 1)) <= 4096
 	  && INTVAL (XEXP (idx, 1)) >= -4096)
 	{
-	  int val = INTVAL (XEXP (XEXP (idx, 0), 1));
+	  HOST_WIDE_INT val = INTVAL (XEXP (XEXP (idx, 0), 1));
 	  rtx reg1, reg2;
 
 	  reg1 = force_reg (Pmode, gen_rtx_PLUS (Pmode, base, XEXP (idx, 1)));
@@ -1232,7 +1232,7 @@ hppa_legitimize_address (rtx x, rtx oldx ATTRIBUTE_UNU
 	      && GET_CODE (XEXP (XEXP (x, 0), 1)) == CONST_INT
 	      && shadd_constant_p (INTVAL (XEXP (XEXP (x, 0), 1))))
 	    {
-	      int val = INTVAL (XEXP (XEXP (x, 0), 1));
+	      HOST_WIDE_INT val = INTVAL (XEXP (XEXP (x, 0), 1));
 	      rtx reg1, reg2;
 
 	      reg1 = XEXP (x, 1);
@@ -1686,6 +1686,11 @@ emit_move_sequence (rtx *operands, enum machine_mode m
   /* Handle the most common case: storing into a register.  */
   else if (register_operand (operand0, mode))
     {
+      /* Legitimize TLS symbol references.  This happens for references
+	 that aren't a legitimate constant.  */
+      if (PA_SYMBOL_REF_TLS_P (operand1))
+	operand1 = legitimize_tls_address (operand1);
+
       if (register_operand (operand1, mode)
 	  || (GET_CODE (operand1) == CONST_INT
 	      && cint_ok_for_move (INTVAL (operand1)))
@@ -2650,8 +2655,8 @@ find_addr_reg (rtx addr)
 const char *
 output_block_move (rtx *operands, int size_is_constant ATTRIBUTE_UNUSED)
 {
-  int align = INTVAL (operands[5]);
-  unsigned long n_bytes = INTVAL (operands[4]);
+  HOST_WIDE_INT align = INTVAL (operands[5]);
+  unsigned HOST_WIDE_INT n_bytes = INTVAL (operands[4]);
 
   /* We can't move more than a word at a time because the PA
      has no longer integer move insns.  (Could use fp mem ops?)  */
@@ -2778,8 +2783,8 @@ static int
 compute_movmem_length (rtx insn)
 {
   rtx pat = PATTERN (insn);
-  unsigned int align = INTVAL (XEXP (XVECEXP (pat, 0, 7), 0));
-  unsigned long n_bytes = INTVAL (XEXP (XVECEXP (pat, 0, 6), 0));
+  unsigned HOST_WIDE_INT align = INTVAL (XEXP (XVECEXP (pat, 0, 7), 0));
+  unsigned HOST_WIDE_INT n_bytes = INTVAL (XEXP (XVECEXP (pat, 0, 6), 0));
   unsigned int n_insns = 0;
 
   /* We can't move more than four bytes at a time because the PA
@@ -2814,8 +2819,8 @@ compute_movmem_length (rtx insn)
 const char *
 output_block_clear (rtx *operands, int size_is_constant ATTRIBUTE_UNUSED)
 {
-  int align = INTVAL (operands[3]);
-  unsigned long n_bytes = INTVAL (operands[2]);
+  HOST_WIDE_INT align = INTVAL (operands[3]);
+  unsigned HOST_WIDE_INT n_bytes = INTVAL (operands[2]);
 
   /* We can't clear more than a word at a time because the PA
      has no longer integer move insns.  */
@@ -2920,8 +2925,8 @@ static int
 compute_clrmem_length (rtx insn)
 {
   rtx pat = PATTERN (insn);
-  unsigned int align = INTVAL (XEXP (XVECEXP (pat, 0, 4), 0));
-  unsigned long n_bytes = INTVAL (XEXP (XVECEXP (pat, 0, 3), 0));
+  unsigned HOST_WIDE_INT align = INTVAL (XEXP (XVECEXP (pat, 0, 4), 0));
+  unsigned HOST_WIDE_INT n_bytes = INTVAL (XEXP (XVECEXP (pat, 0, 3), 0));
   unsigned int n_insns = 0;
 
   /* We can't clear more than a word at a time because the PA
@@ -5337,7 +5342,7 @@ pa_som_file_start (void)
 static void
 pa_linux_file_start (void)
 {
-  pa_file_start_file (1);
+  pa_file_start_file (0);
   pa_file_start_level ();
   pa_file_start_mcount ("CODE");
 }
@@ -5552,7 +5557,7 @@ emit_hpdiv_const (rtx *operands, int unsignedp)
 const char *
 output_div_insn (rtx *operands, int unsignedp, rtx insn)
 {
-  int divisor;
+  HOST_WIDE_INT divisor;
 
   /* If the divisor is a constant, try to use one of the special
      opcodes .*/
