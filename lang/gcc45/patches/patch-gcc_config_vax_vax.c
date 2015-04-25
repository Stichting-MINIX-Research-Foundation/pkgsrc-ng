$NetBSD$

--- gcc/config/vax/vax.c.orig	Tue Sep 22 15:16:34 2009
+++ gcc/config/vax/vax.c
@@ -300,7 +300,10 @@ print_operand_address (FILE * file, rtx addr)
 	  addr = XEXP (addr, 1);
 	}
       else
-	gcc_unreachable ();
+	{
+	   debug_rtx (orig);
+	   gcc_unreachable ();
+	}
 
       if (REG_P (addr))
 	{
@@ -311,9 +314,8 @@ print_operand_address (FILE * file, rtx addr)
 	}
       else if (GET_CODE (addr) == MULT)
 	ireg = addr;
-      else
+      else if (GET_CODE (addr) == PLUS)
 	{
-	  gcc_assert (GET_CODE (addr) == PLUS);
 	  if (CONSTANT_ADDRESS_P (XEXP (addr, 0))
 	      || MEM_P (XEXP (addr, 0)))
 	    {
@@ -321,11 +323,15 @@ print_operand_address (FILE * file, rtx addr)
 		{
 		  if (CONST_INT_P (offset))
 		    offset = plus_constant (XEXP (addr, 0), INTVAL (offset));
-		  else
+		  else if (CONST_INT_P (XEXP (addr, 0)))
 		    {
-		      gcc_assert (CONST_INT_P (XEXP (addr, 0)));
 		      offset = plus_constant (offset, INTVAL (XEXP (addr, 0)));
 		    }
+		  else
+		    {
+		      debug_rtx (orig);
+		      gcc_unreachable ();
+		    }
 		}
 	      offset = XEXP (addr, 0);
 	    }
@@ -336,12 +342,15 @@ print_operand_address (FILE * file, rtx addr)
 	      else
 		reg1 = XEXP (addr, 0);
 	    }
-	  else
+	  else if (GET_CODE (XEXP (addr, 0)) == MULT && !ireg)
 	    {
-	      gcc_assert (GET_CODE (XEXP (addr, 0)) == MULT);
-	      gcc_assert (!ireg);
 	      ireg = XEXP (addr, 0);
 	    }
+	  else
+	    {
+	      debug_rtx (orig);
+	      gcc_unreachable ();
+	    }
 
 	  if (CONSTANT_ADDRESS_P (XEXP (addr, 1))
 	      || MEM_P (XEXP (addr, 1)))
@@ -365,13 +374,21 @@ print_operand_address (FILE * file, rtx addr)
 	      else
 		reg1 = XEXP (addr, 1);
 	    }
-	  else
+	  else if (GET_CODE (XEXP (addr, 1)) == MULT && !ireg)
 	    {
-	      gcc_assert (GET_CODE (XEXP (addr, 1)) == MULT);
-	      gcc_assert (!ireg);
 	      ireg = XEXP (addr, 1);
 	    }
+	  else
+	    {
+	      debug_rtx (orig);
+	      gcc_unreachable ();
+	    }
 	}
+      else
+	{
+	  debug_rtx (orig);
+	  gcc_unreachable ();
+	}
 
       /* If REG1 is nonzero, figure out if it is a base or index register.  */
       if (reg1)
@@ -382,7 +399,11 @@ print_operand_address (FILE * file, rtx addr)
 		  && (MEM_P (offset)
 		      || (flag_pic && symbolic_operand (offset, SImode)))))
 	    {
-	      gcc_assert (!ireg);
+	      if (ireg)
+		{
+		  debug_rtx (orig);
+		  gcc_unreachable ();
+		}
 	      ireg = reg1;
 	    }
 	  else
@@ -428,12 +449,17 @@ print_operand_address (FILE * file, rtx addr)
 	{
 	  if (GET_CODE (ireg) == MULT)
 	    ireg = XEXP (ireg, 0);
-	  gcc_assert (REG_P (ireg));
+	  if (! REG_P (ireg))
+	    {
+	      debug_rtx (orig);
+	      output_operand_lossage ("non-register index expression");
+	    }
 	  fprintf (file, "[%s]", reg_names[REGNO (ireg)]);
 	}
       break;
 
     default:
+      gcc_assert (! REG_P(addr));
       output_addr_const (file, addr);
     }
 }
@@ -1127,7 +1153,7 @@ vax_output_int_move (rtx insn ATTRIBUTE_UNUSED, rtx *o
 		{
 		  operands[1] = GEN_INT (lval);
 		  operands[2] = GEN_INT (n);
-		  return "ashq %2,%1,%0";
+		  return "ashq %2,%D1,%0";
 		}
 #if HOST_BITS_PER_WIDE_INT == 32
 	    }
@@ -1139,7 +1165,7 @@ vax_output_int_move (rtx insn ATTRIBUTE_UNUSED, rtx *o
 	    {
 	      operands[1] = GEN_INT (hval >> n);
 	      operands[2] = GEN_INT (n + 32);
-	      return "ashq %2,%1,%0";
+	      return "ashq %2,%D1,%0";
 #endif
 	    }
 	}
@@ -1566,6 +1592,111 @@ vax_output_int_subtract (rtx insn, rtx *operands, enum
   }
 }
 
+static rtx
+mkrtx(enum rtx_code code, enum machine_mode mode, rtx base, HOST_WIDE_INT off)
+{
+  rtx tmp;
+
+  if (GET_CODE (base) == CONST)
+    base = XEXP (base, 0);
+
+  if (GET_CODE (base) == PLUS)
+    {
+      rtx a = XEXP (base, 0);
+      rtx b = XEXP (base, 1);
+      if (GET_CODE (b) == CONST)
+	b = XEXP (b, 0);
+      if (CONST_INT_P (b))
+	{
+          off += INTVAL (b);
+          base = a;
+	}
+      else if (REG_P (a) && GET_CODE (b) == SYMBOL_REF)
+	{
+	  if (off != 0)
+	    {
+	      base = gen_rtx_PLUS (Pmode, a, plus_constant(b, off));
+	      off = 0;
+	    }
+	}
+      else if (REG_P (a) && GET_CODE (b) == PLUS)
+	{
+          off += INTVAL (XEXP (b, 1));
+	  base = gen_rtx_PLUS (Pmode, a, plus_constant(XEXP (b, 0), off));
+	  off = 0;
+	}
+      else
+        {
+	  debug_rtx(base);
+	  gcc_unreachable ();
+	}
+    }
+  if (code == POST_INC)
+    tmp = gen_rtx_POST_INC (SImode, base);
+  else if (off == 0 || (REG_P (base) && code == REG))
+    tmp = base;
+  else
+    tmp = plus_constant (base, off);
+  return gen_rtx_MEM (mode, tmp);
+}
+
+const char *
+vax_output_movmemsi (rtx insn, rtx *operands)
+{
+  HOST_WIDE_INT n = INTVAL (operands[2]);
+  HOST_WIDE_INT off;
+  rtx src, dest;
+  const char *pat = NULL;
+  const enum rtx_code *src_codes;
+  const enum rtx_code *dest_codes;
+  int code_idx = 0;
+  int mode_idx;
+
+  static const enum machine_mode xmodes[4] =
+    {
+      QImode, HImode, SImode, DImode
+    };
+  static const char * const pats[4] = 
+    {
+      "movb %1,%0", "movw %1,%0", "movl %1,%0", "movq %1,%0", 
+    };
+  static const enum rtx_code codes[2][3] =
+    {
+      { PLUS, PLUS, PLUS },
+      { POST_INC, POST_INC, REG },
+    };
+
+  src = XEXP (operands[1], 0);
+
+  src_codes =
+    codes[REG_P (src) && find_regno_note (insn, REG_DEAD, REGNO(src))];
+
+  dest = XEXP (operands[0], 0);
+
+  dest_codes =
+    codes[REG_P (dest) && find_regno_note (insn, REG_DEAD, REGNO(dest))];
+
+  for (off = 0, code_idx = 0, mode_idx = 3; mode_idx >= 0; mode_idx--)
+    {
+      const enum machine_mode mode = xmodes[mode_idx];
+      const HOST_WIDE_INT mode_len = GET_MODE_SIZE (mode);
+      for (; n >= mode_len; n -= mode_len, off += mode_len)
+	{
+	  if (pat != NULL)
+	    output_asm_insn (pat, operands);
+	  if (n == mode_len)
+	    code_idx = 2;
+	  operands[0] = mkrtx(dest_codes[code_idx], mode, dest, off);
+	  operands[1] = mkrtx(src_codes[code_idx], mode, src, off);
+	  if (pat == NULL)
+	    code_idx = 1;
+	  pat = pats[mode_idx];
+	}
+    }
+
+  return pat;
+}
+
 /* True if X is an rtx for a constant that is a valid address.  */
 
 bool
@@ -1582,6 +1713,7 @@ legitimate_constant_address_p (rtx x)
       && !SYMBOL_REF_LOCAL_P (XEXP (XEXP (x, 0), 0)))
     return false;
 #endif
+   gcc_assert (! REG_P (x));
    return true;
 }
 
@@ -1901,8 +2033,10 @@ vax_expand_addsub_di_operands (rtx * operands, enum rt
 	 and that's just a left shift of 1.  */
       if (rtx_equal_p (operands[1], operands[2]))
 	{
-	  gcc_assert (code != MINUS);
-	  emit_insn (gen_ashldi3 (operands[0], operands[1], const1_rtx));
+	  if (code == MINUS)
+	    emit_insn (gen_movdi (operands[0], const0_rtx));
+	  else
+	    emit_insn (gen_ashldi3 (operands[0], operands[1], const1_rtx));
 	  return;
 	}
 
