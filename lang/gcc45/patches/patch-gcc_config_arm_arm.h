$NetBSD$

--- gcc/config/arm/arm.h.orig	Wed Dec 23 16:36:40 2009
+++ gcc/config/arm/arm.h
@@ -94,7 +94,14 @@ extern char arm_arch_name[];
 	if (arm_arch_iwmmxt)				\
 	  builtin_define ("__IWMMXT__");		\
 	if (TARGET_AAPCS_BASED)				\
-	  builtin_define ("__ARM_EABI__");		\
+	  {						\
+	    builtin_define ("__ARM_EABI__");		\
+	    builtin_define ("__ARM_PCS");		\
+	    if (TARGET_HARD_FLOAT && TARGET_VFP)	\
+	      builtin_define ("__ARM_PCS_VFP");		\
+	  }						\
+	if (TARGET_IDIV)				\
+	  builtin_define ("__ARM_ARCH_EXT_IDIV__");	\
     } while (0)
 
 /* The various ARM cores.  */
@@ -264,6 +271,8 @@ extern void (*arm_lang_output_object_attributes_hook)(
    for Thumb-2.  */
 #define TARGET_UNIFIED_ASM TARGET_THUMB2
 
+/* Nonzero if integer division instructions supported.  */
+#define TARGET_IDIV (arm_arch_hwdiv)
 
 /* True iff the full BPABI is being used.  If TARGET_BPABI is true,
    then TARGET_AAPCS_BASED must be true -- but the converse does not
@@ -2111,7 +2120,7 @@ typedef struct
   (GET_CODE (X) == REG && ARM_REG_OK_FOR_INDEX_P (X))
 
 /* Define this for compatibility reasons. */
-#define HANDLE_PRAGMA_PACK_PUSH_POP
+#define HANDLE_PRAGMA_PACK_PUSH_POP 1
 
 /* Specify the machine mode that this machine uses
    for the index in the tablejump instruction.  */
