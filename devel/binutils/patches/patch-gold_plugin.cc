$NetBSD$

--- gold/plugin.cc.orig	Tue Jun 12 22:52:41 2012
+++ gold/plugin.cc
@@ -29,8 +29,38 @@
 #include <vector>
 
 #ifdef ENABLE_PLUGINS
+#ifdef HAVE_DLFCN_H
 #include <dlfcn.h>
+#elif defined (HAVE_WINDOWS_H)
+#include <windows.h>
+#else
+#error Unknown how to handle dynamic-load-libraries.
 #endif
+
+#if !defined (HAVE_DLFCN_H) && defined (HAVE_WINDOWS_H)
+
+#define RTLD_NOW 0      /* Dummy value.  */
+static void *
+dlopen(const char *file, int mode ATTRIBUTE_UNUSED)
+{
+  return LoadLibrary(file);
+}
+
+static void *
+dlsym(void *handle, const char *name)
+{
+  return reinterpret_cast<void *>(
+     GetProcAddress(static_cast<HMODULE>(handle),name));
+}
+
+static const char *
+dlerror(void)
+{
+  return "unable to load dll";
+}
+
+#endif /* !defined (HAVE_DLFCN_H) && defined (HAVE_WINDOWS_H)  */
+#endif /* ENABLE_PLUGINS */
 
 #include "parameters.h"
 #include "errors.h"
