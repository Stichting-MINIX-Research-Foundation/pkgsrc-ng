$NetBSD$

--- libobjc/sendmsg.c.orig	Thu Apr  9 15:00:19 2009
+++ libobjc/sendmsg.c
@@ -90,7 +90,6 @@ Method_t search_for_method_in_list (MethodList_t list,
 id nil_method (id, SEL);
 
 /* Given a selector, return the proper forwarding implementation. */
-inline
 IMP
 __objc_get_forward_imp (id rcv, SEL sel)
 {
@@ -129,7 +128,6 @@ __objc_get_forward_imp (id rcv, SEL sel)
 }
 
 /* Given a class and selector, return the selector's implementation.  */
-inline
 IMP
 get_imp (Class class, SEL sel)
 {
@@ -190,7 +188,6 @@ get_imp (Class class, SEL sel)
 /* Query if an object can respond to a selector, returns YES if the
 object implements the selector otherwise NO.  Does not check if the
 method can be forwarded. */
-inline
 BOOL
 __objc_responds_to (id object, SEL sel)
 {
@@ -215,7 +212,6 @@ __objc_responds_to (id object, SEL sel)
 /* This is the lookup function.  All entries in the table are either a 
    valid method *or* zero.  If zero then either the dispatch table
    needs to be installed or it doesn't exist and forwarding is attempted. */
-inline
 IMP
 objc_msg_lookup (id receiver, SEL op)
 {
@@ -705,7 +701,6 @@ __objc_print_dtable_stats ()
 /* Returns the uninstalled dispatch table indicator.
  If a class' dispatch table points to __objc_uninstalled_dtable
  then that means it needs its dispatch table to be installed. */
-inline
 struct sarray *
 objc_get_uninstalled_dtable ()
 {
