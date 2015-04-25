$NetBSD$

--- gcc/config/avr/libgcc.S.orig	Sat May 23 07:16:07 2009
+++ gcc/config/avr/libgcc.S
@@ -28,6 +28,7 @@ see the files COPYING3 and COPYING.RUNTIME respectivel
 #define __SP_H__ 0x3e
 #define __SP_L__ 0x3d
 #define __RAMPZ__ 0x3B
+#define __EIND__  0x3C
 
 /* Most of the functions here are called directly from avr.md
    patterns, instead of using the standard libcall mechanisms.
@@ -689,7 +690,8 @@ __tablejump__:
 	lpm
 	push	r0
 #if defined (__AVR_HAVE_EIJMP_EICALL__)
-        push    __zero_reg__
+	in   __tmp_reg__, __EIND__
+	push __tmp_reg__
 #endif
 	ret
 #endif
@@ -791,22 +793,22 @@ __do_clear_bss:
 #if defined(__AVR_HAVE_RAMPZ__)
 __do_global_ctors:
 	ldi	r17, hi8(__ctors_start)
-	ldi	r16, hh8(__ctors_start)
 	ldi	r28, lo8(__ctors_end)
 	ldi	r29, hi8(__ctors_end)
-	ldi	r20, hh8(__ctors_end)
+	ldi	r16, hh8(__ctors_end)
 	rjmp	.L__do_global_ctors_start
 .L__do_global_ctors_loop:
 	sbiw	r28, 2
-	sbc     r20, __zero_reg__
+	sbc     r16, __zero_reg__
 	mov_h	r31, r29
 	mov_l	r30, r28
-	out     __RAMPZ__, r20
+	out     __RAMPZ__, r16
 	XCALL	__tablejump_elpm__
 .L__do_global_ctors_start:
 	cpi	r28, lo8(__ctors_start)
 	cpc	r29, r17
-	cpc	r20, r16
+	ldi	r24, hh8(__ctors_start)
+	cpc	r16, r24
 	brne	.L__do_global_ctors_loop
 #else
 __do_global_ctors:
@@ -832,22 +834,22 @@ __do_global_ctors:
 #if defined(__AVR_HAVE_RAMPZ__)
 __do_global_dtors:
 	ldi	r17, hi8(__dtors_end)
-	ldi	r16, hh8(__dtors_end)
 	ldi	r28, lo8(__dtors_start)
 	ldi	r29, hi8(__dtors_start)
-	ldi	r20, hh8(__dtors_start)
+	ldi	r16, hh8(__dtors_start)
 	rjmp	.L__do_global_dtors_start
 .L__do_global_dtors_loop:
 	sbiw	r28, 2
-	sbc     r20, __zero_reg__
+	sbc     r16, __zero_reg__
 	mov_h	r31, r29
 	mov_l	r30, r28
-	out     __RAMPZ__, r20
+	out     __RAMPZ__, r16
 	XCALL	__tablejump_elpm__
 .L__do_global_dtors_start:
 	cpi	r28, lo8(__dtors_end)
 	cpc	r29, r17
-	cpc	r20, r16
+	ldi	r24, hh8(__dtors_end)
+	cpc	r16, r24
 	brne	.L__do_global_dtors_loop
 #else
 __do_global_dtors:
@@ -889,7 +891,8 @@ __tablejump_elpm__:
 	elpm
 	push	r0
 #if defined (__AVR_HAVE_EIJMP_EICALL__)
-        push    __zero_reg__
+	in      __tmp_reg__, __EIND__
+	push    __tmp_reg__
 #endif
 	ret
 #endif
