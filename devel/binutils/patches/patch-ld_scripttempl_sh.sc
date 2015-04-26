$NetBSD$

--- ld/scripttempl/sh.sc.orig	Wed Sep 25 17:06:09 2002
+++ ld/scripttempl/sh.sc
@@ -6,17 +6,14 @@ TORS=".tors :
     ___dtors = . ;
     *(.dtors)
     ___dtors_end = . ;
-  } > ram"
+  }"
 
+
 cat <<EOF
 OUTPUT_FORMAT("${OUTPUT_FORMAT}")
 OUTPUT_ARCH(${ARCH})
+${LIB_SEARCH_DIRS}
 
-MEMORY
-{
-  ram : o = 0x1000, l = 512k
-}
-
 SECTIONS
 {
   .text :
@@ -24,9 +21,9 @@ SECTIONS
     *(.text)
     *(.strings)
     ${RELOCATING+ _etext = . ; }
-  } ${RELOCATING+ > ram}
+  }
   ${CONSTRUCTING+${TORS}}
-  .data :
+  .data  ${RELOCATING+ ALIGN(${TARGET_PAGE_SIZE})} :
   {
     *(.data)
     ${RELOCATING+*(.gcc_exc*)}
@@ -35,19 +32,19 @@ SECTIONS
     ${RELOCATING+___EH_FRAME_END__ = . ;}
     ${RELOCATING+LONG(0);}
     ${RELOCATING+ _edata = . ; }
-  } ${RELOCATING+ > ram}
-  .bss :
+  }
+  .bss ${RELOCATING+ ALIGN(${TARGET_PAGE_SIZE})} :
   {
     ${RELOCATING+ _bss_start = . ; }
     *(.bss)
     *(COMMON)
     ${RELOCATING+ _end = . ;  }
-  } ${RELOCATING+ > ram}
-  .stack ${RELOCATING+ 0x30000 }  :
+  }
+  .stack :
   {
     ${RELOCATING+ _stack = . ; }
     *(.stack)
-  } ${RELOCATING+ > ram}
+  }
   .stab 0 ${RELOCATING+(NOLOAD)} :
   {
     *(.stab)
