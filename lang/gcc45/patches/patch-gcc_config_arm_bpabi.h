$NetBSD$

--- gcc/config/arm/bpabi.h.orig	Fri Nov 20 17:37:30 2009
+++ gcc/config/arm/bpabi.h
@@ -20,13 +20,18 @@
    <http://www.gnu.org/licenses/>.  */
 
 /* Use the AAPCS ABI by default.  */
+#undef ARM_DEFAULT_ABI
 #define ARM_DEFAULT_ABI ARM_ABI_AAPCS
 
 /* Assume that AAPCS ABIs should adhere to the full BPABI.  */ 
+#undef TARGET_BPABI
 #define TARGET_BPABI (TARGET_AAPCS_BASED)
 
 /* BPABI targets use EABI frame unwinding tables.  */
+#undef MUST_USE_SJLJ_EXCEPTIONS
 #define TARGET_UNWIND_INFO 1
+#undef ARM_EABI_UNWIND_TABLES
+#define ARM_EABI_UNWIND_TABLES 1
 
 /* Section 4.1 of the AAPCS requires the use of VFP format.  */
 #undef  FPUTYPE_DEFAULT
@@ -72,17 +77,10 @@
 #undef  LINK_SPEC
 #define LINK_SPEC BPABI_LINK_SPEC
 
-#if defined (__thumb__)
-#define RENAME_LIBRARY_SET ".thumb_set"
-#else
-#define RENAME_LIBRARY_SET ".set"
-#endif
-
 /* Make __aeabi_AEABI_NAME an alias for __GCC_NAME.  */
 #define RENAME_LIBRARY(GCC_NAME, AEABI_NAME)		\
-  __asm__ (".globl\t__aeabi_" #AEABI_NAME "\n"		\
-	   RENAME_LIBRARY_SET "\t__aeabi_" #AEABI_NAME 	\
-	     ", __" #GCC_NAME "\n");
+  typeof (__##GCC_NAME) __aeabi_##AEABI_NAME \
+    __attribute__((alias ("__" #GCC_NAME)));
 
 /* Give some libgcc functions an additional __aeabi name.  */
 #ifdef L_muldi3
