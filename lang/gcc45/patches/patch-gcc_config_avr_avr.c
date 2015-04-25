$NetBSD$

--- gcc/config/avr/avr.c.orig	Thu Mar  3 16:58:26 2011
+++ gcc/config/avr/avr.c
@@ -1043,8 +1043,7 @@ avr_legitimate_address_p (enum machine_mode mode, rtx 
 		 true_regnum (XEXP (x, 0)));
       debug_rtx (x);
     }
-  if (!strict && GET_CODE (x) == SUBREG)
-	x = SUBREG_REG (x);
+  
   if (REG_P (x) && (strict ? REG_OK_FOR_BASE_STRICT_P (x)
                     : REG_OK_FOR_BASE_NOSTRICT_P (x)))
     r = POINTER_REGS;
@@ -1386,9 +1385,8 @@ notice_update_cc (rtx body ATTRIBUTE_UNUSED, rtx insn)
 	    {
 	      rtx x = XEXP (src, 1);
 
-	      if (GET_CODE (x) == CONST_INT
-		  && INTVAL (x) > 0
-		  && INTVAL (x) != 6)
+	      if (CONST_INT_P (x)
+		  && IN_RANGE (INTVAL (x), 1, 5))
 		{
 		  cc_status.value1 = SET_DEST (set);
 		  cc_status.flags |= CC_OVERFLOW_UNUSABLE;
@@ -5934,26 +5932,30 @@ jump_over_one_insn_p (rtx insn, rtx dest)
 int
 avr_hard_regno_mode_ok (int regno, enum machine_mode mode)
 {
-  /* Disallow QImode in stack pointer regs.  */
-  if ((regno == REG_SP || regno == (REG_SP + 1)) && mode == QImode)
-    return 0;
-
-  /* The only thing that can go into registers r28:r29 is a Pmode.  */
-  if (regno == REG_Y && mode == Pmode)
+  /* NOTE: 8-bit values must not be disallowed for R28 or R29.
+        Disallowing QI et al. in these regs might lead to code like
+            (set (subreg:QI (reg:HI 28) n) ...)
+        which will result in wrong code because reload does not
+        handle SUBREGs of hard regsisters like this, see PR46779.
+        This could be fixed in reload.  However, it appears
+        that fixing reload is not wanted by reload people.  */
+  
+  /* Any GENERAL_REGS register can hold 8-bit values.  */
+  
+  if (GET_MODE_SIZE (mode) == 1)
     return 1;
 
-  /* Otherwise disallow all regno/mode combinations that span r28:r29.  */
-  if (regno <= (REG_Y + 1) && (regno + GET_MODE_SIZE (mode)) >= (REG_Y + 1))
+  /* FIXME: Ideally, the following test is not needed.
+        However, it turned out that it can reduce the number
+        of spill fails.  AVR and it's poor endowment with
+        address registers is extreme stress test for reload.  */
+  
+  if (GET_MODE_SIZE (mode) >= 4
+      && regno >= REG_X)
     return 0;
 
-  if (mode == QImode)
-    return 1;
-
-  /* Modes larger than QImode occupy consecutive registers.  */
-  if (regno + GET_MODE_SIZE (mode) > FIRST_PSEUDO_REGISTER)
-    return 0;
-
-  /* All modes larger than QImode should start in an even register.  */
+  /* All modes larger than 8 bits should start in an even register.  */
+  
   return !(regno & 1);
 }
 
@@ -6080,13 +6082,23 @@ avr_hard_regno_scratch_ok (unsigned int regno)
       && !df_regs_ever_live_p (regno))
     return false;
 
+  /* Don't allow hard registers that might be part of the frame pointer.
+     Some places in the compiler just test for [HARD_]FRAME_POINTER_REGNUM
+     and don't care for a frame pointer that spans more than one register.  */
+
+  if ((!reload_completed || frame_pointer_needed)
+      && (regno == REG_Y || regno == REG_Y + 1))
+    {
+      return false;
+    }
+
   return true;
 }
 
 /* Return nonzero if register OLD_REG can be renamed to register NEW_REG.  */
 
 int
-avr_hard_regno_rename_ok (unsigned int old_reg ATTRIBUTE_UNUSED,
+avr_hard_regno_rename_ok (unsigned int old_reg,
 			  unsigned int new_reg)
 {
   /* Interrupt functions can only use registers that have already been
@@ -6097,6 +6109,17 @@ avr_hard_regno_rename_ok (unsigned int old_reg ATTRIBU
       && !df_regs_ever_live_p (new_reg))
     return 0;
 
+  /* Don't allow hard registers that might be part of the frame pointer.
+     Some places in the compiler just test for [HARD_]FRAME_POINTER_REGNUM
+     and don't care for a frame pointer that spans more than one register.  */
+
+  if ((!reload_completed || frame_pointer_needed)
+      && (old_reg == REG_Y || old_reg == REG_Y + 1
+          || new_reg == REG_Y || new_reg == REG_Y + 1))
+    {
+      return 0;
+    }
+  
   return 1;
 }
 
