$NetBSD$

--- libstdc++-v3/include/bits/stl_queue.h.orig	Thu Feb  4 18:20:34 2010
+++ libstdc++-v3/include/bits/stl_queue.h
@@ -1,6 +1,6 @@
 // Queue implementation -*- C++ -*-
 
-// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009
+// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010
 // Free Software Foundation, Inc.
 //
 // This file is part of the GNU ISO C++ Library.  This library is free
@@ -137,16 +137,6 @@ _GLIBCXX_BEGIN_NAMESPACE(std)
       explicit
       queue(_Sequence&& __c = _Sequence())
       : c(std::move(__c)) { }
-
-      queue(queue&& __q)
-      : c(std::move(__q.c)) { }
-
-      queue&
-      operator=(queue&& __q)
-      {
-	c = std::move(__q.c);
-	return *this;
-      }
 #endif
 
       /**
@@ -451,17 +441,6 @@ _GLIBCXX_BEGIN_NAMESPACE(std)
 	  c.insert(c.end(), __first, __last);
 	  std::make_heap(c.begin(), c.end(), comp);
 	}
-
-      priority_queue(priority_queue&& __pq)
-      : c(std::move(__pq.c)), comp(std::move(__pq.comp)) { }
-
-      priority_queue&
-      operator=(priority_queue&& __pq)
-      {
-	c = std::move(__pq.c);
-	comp = std::move(__pq.comp);
-	return *this;
-      }
 #endif
 
       /**
