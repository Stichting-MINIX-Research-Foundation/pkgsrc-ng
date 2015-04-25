$NetBSD$

--- gcc/testsuite/gcc.c-torture/compile/pr38752.c.orig	Wed May 21 19:48:57 2014
+++ gcc/testsuite/gcc.c-torture/compile/pr38752.c
@@ -0,0 +1,25 @@
+typedef struct
+{
+  int             baddr;
+} mstruct_t;
+
+static struct
+{
+  unsigned int    mapnum;
+  mstruct_t       unused;
+} mtab;
+
+static mstruct_t *mactab = &mtab.unused;
+
+int
+main(void)
+{
+  int i;
+  int addr;
+
+  for (i=1; i <= mtab.mapnum; i++)
+    if (addr < mactab[i].baddr)
+      break;
+  return 0;
+}
+
