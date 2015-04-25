$NetBSD$

--- gcc/gcov-iov.c.orig	Thu Jul 26 08:37:01 2007
+++ gcc/gcov-iov.c
@@ -19,8 +19,8 @@ You should have received a copy of the GNU General Pub
 along with GCC; see the file COPYING3.  If not see
 <http://www.gnu.org/licenses/>.  */
 
-#include <stdio.h>
-#include <stdlib.h>
+#include "bconfig.h"
+#include "system.h"
 
 /* Command line arguments are the base GCC version and the development
    phase (the latter may be an empty string).  */
@@ -48,8 +48,14 @@ main (int argc, char **argv)
   if (*ptr == '.')
     minor = strtoul (ptr + 1, 0, 10);
 
+  /* For releases the development phase is an empty string, for
+     prerelease versions on a release branch it is "prerelease".
+     Consider both equal as patch-level releases do not change
+     the GCOV version either.
+     On the trunk the development phase is "experimental".  */
   phase = argv[2][0];
-  if (phase == '\0')
+  if (phase == '\0'
+      || strcmp (argv[2], "prerelease") == 0)
     phase = '*';
 
   v[0] = (major < 10 ? '0' : 'A' - 10) + major;
