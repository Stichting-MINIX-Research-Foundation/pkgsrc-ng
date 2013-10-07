$NetBSD$

--- opcodes/mips-opc.c.orig	Tue Sep  4 14:21:10 2012
+++ opcodes/mips-opc.c
@@ -791,10 +791,12 @@ const struct mips_opcode mips_builtin_opcodes[] =
 {"hibernate","",        0x42000023, 0xffffffff,	0, 			0,		V1	},
 {"ins",     "t,r,+A,+B", 0x7c000004, 0xfc00003f, WR_t|RD_s,    		0,		I33	},
 {"iret",    "",		0x42000038, 0xffffffff,	NODS,			0,		MC	},
+{"jr",      "s",	0,        (int) M_JR_S, INSN_MACRO,		0,		I1	},
 {"jr",      "s",	0x00000008, 0xfc1fffff,	UBD|RD_s,		0,		I1	},
 /* jr.hb is officially MIPS{32,64}R2, but it works on R1 as jr with
    the same hazard barrier effect.  */
 {"jr.hb",   "s",	0x00000408, 0xfc1fffff,	UBD|RD_s,		0,		I32	},
+{"j",       "s",	0,         (int) M_J_S, INSN_MACRO,		0,		I1	},
 {"j",       "s",	0x00000008, 0xfc1fffff,	UBD|RD_s,		0,		I1	}, /* jr */
 /* SVR4 PIC code requires special handling for j, so it must be a
    macro.  */
@@ -803,7 +805,9 @@ const struct mips_opcode mips_builtin_opcodes[] =
    assembler, but will never match user input (because the line above
    will match first).  */
 {"j",       "a",	0x08000000, 0xfc000000,	UBD,			0,		I1	},
+{"jalr",    "s",	0,      (int) M_JALR_S, INSN_MACRO,             0,		I1	},
 {"jalr",    "s",	0x0000f809, 0xfc1fffff,	UBD|RD_s|WR_d,		0,		I1	},
+{"jalr",    "d,s",	0,     (int) M_JALR_DS, INSN_MACRO,		0,		I1	},
 {"jalr",    "d,s",	0x00000009, 0xfc1f07ff,	UBD|RD_s|WR_d,		0,		I1	},
 /* jalr.hb is officially MIPS{32,64}R2, but it works on R1 as jalr
    with the same hazard barrier effect.  */
