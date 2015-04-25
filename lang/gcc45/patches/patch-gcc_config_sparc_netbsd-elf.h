$NetBSD$

--- gcc/config/sparc/netbsd-elf.h.orig	Thu Aug  2 10:49:31 2007
+++ gcc/config/sparc/netbsd-elf.h
@@ -112,7 +112,7 @@ along with GCC; see the file COPYING3.  If not see
    + MASK_STACK_BIAS + MASK_APP_REGS + MASK_FPU + MASK_LONG_DOUBLE_128)
 
 #undef SPARC_DEFAULT_CMODEL
-#define SPARC_DEFAULT_CMODEL CM_MEDANY
+#define SPARC_DEFAULT_CMODEL CM_MEDMID
 
 #endif
 
@@ -134,7 +134,8 @@ along with GCC; see the file COPYING3.  If not see
 	        %{!msupersparc:-mcpu=ultrasparc}}}}}}} \
     %{!mno-vis:%{!mcpu=v9:-mvis}} \
     %{p:-mcmodel=medlow} \
-    %{pg:-mcmodel=medlow}}"
+    %{pg:-mcmodel=medlow}} " \
+  NETBSD_CC1_AND_CC1PLUS_SPEC
 
 #define CC1_SPEC64 \
  "%{sun4:} %{target:} \
@@ -153,9 +154,29 @@ along with GCC; see the file COPYING3.  If not see
 	      %{!mv8*: \
 		%{!msupersparc:-mcpu=cypress}}}}}}}} \
   %{!m32: \
-    %{p:-mcmodel=medlow} \
-    %{pg:-mcmodel=medlow}}"
+      %{p:-mcmodel=medlow} \
+      %{pg:-mcmodel=medlow}} " \
+  NETBSD_CC1_AND_CC1PLUS_SPEC
 
+#if defined(SPARC_BI_ARCH) || defined(__arch64__)
+/* add code model specific object to the link line for 64bit */
+#define	LINK_SPEC_CODE_MODEL64	\
+	"%{!shared:"	\
+	    "%{!mcmodel=*:%:if-exists(%R/usr/lib/sparc_mcmedmid.o)}"	\
+	    "%{mcmodel=medlow:%:if-exists(%R/usr/lib/sparc_mcmedlow.o)}" \
+	    "%{mcmodel=medmid:%:if-exists(%R/usr/lib/sparc_mcmedmid.o)}" \
+	    "%{mcmodel=medany:%:if-exists(%R/usr/lib/sparc_mcmedany.o)}" \
+	"}"
+
+#ifdef SPARC_BI_ARCH
+#define LINK_SPEC_CODE_MODEL	"%{!m32:" LINK_SPEC_CODE_MODEL64 "}"
+#else
+#define	LINK_SPEC_CODE_MODEL	LINK_SPEC_CODE_MODEL64
+#endif
+#else
+#define	LINK_SPEC_CODE_MODEL	""
+#endif
+
 /* Make sure we use the right output format.  Pick a default and then
    make sure -m32/-m64 switch to the right one.  */
 
@@ -172,7 +193,8 @@ along with GCC; see the file COPYING3.  If not see
 #define LINK_SPEC \
  "%(link_arch) \
   %{!mno-relax:%{!r:-relax}} \
-  %(netbsd_link_spec)"
+  %(netbsd_link_spec) " \
+  LINK_SPEC_CODE_MODEL
 
 #define NETBSD_ENTRY_POINT "__start"
 
@@ -263,6 +285,13 @@ along with GCC; see the file COPYING3.  If not see
 	|| TARGET_CPU_DEFAULT == TARGET_CPU_ultrasparc */
 
 #endif	/* SPARC_BI_ARCH */
+
+#ifdef HAVE_AS_TLS
+#undef TARGET_SUN_TLS
+#undef TARGET_GNU_TLS
+#define TARGET_SUN_TLS 0
+#define TARGET_GNU_TLS 1
+#endif
 
 /* We use GNU ld so undefine this so that attribute((init_priority)) works.  */
 #undef CTORS_SECTION_ASM_OP
