$NetBSD$

--- libstdc++-v3/include/ext/ropeimpl.h.orig	Thu Apr  9 15:00:19 2009
+++ libstdc++-v3/include/ext/ropeimpl.h
@@ -378,7 +378,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
 	    _Rope_RopeLeaf<_CharT, _Alloc>* __l
 	      = (_Rope_RopeLeaf<_CharT, _Alloc>*)this;
 	    __l->_Rope_RopeLeaf<_CharT, _Alloc>::~_Rope_RopeLeaf();
-	    _L_deallocate(__l, 1);
+	    this->_L_deallocate(__l, 1);
 	    break;
 	  }
 	case __detail::_S_concat:
@@ -387,7 +387,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
 	      = (_Rope_RopeConcatenation<_CharT, _Alloc>*)this;
 	    __c->_Rope_RopeConcatenation<_CharT, _Alloc>::
 	      ~_Rope_RopeConcatenation();
-	    _C_deallocate(__c, 1);
+	    this->_C_deallocate(__c, 1);
 	    break;
 	  }
 	case __detail::_S_function:
@@ -395,7 +395,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
 	    _Rope_RopeFunction<_CharT, _Alloc>* __f
 	      = (_Rope_RopeFunction<_CharT, _Alloc>*)this;
 	    __f->_Rope_RopeFunction<_CharT, _Alloc>::~_Rope_RopeFunction();
-	    _F_deallocate(__f, 1);
+	    this->_F_deallocate(__f, 1);
 	    break;
 	  }
 	case __detail::_S_substringfn:
@@ -404,7 +404,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
 	      (_Rope_RopeSubstring<_CharT, _Alloc>*)this;
 	    __ss->_Rope_RopeSubstring<_CharT, _Alloc>::
 	      ~_Rope_RopeSubstring();
-	    _S_deallocate(__ss, 1);
+	    this->_S_deallocate(__ss, 1);
 	    break;
 	  }
 	}
@@ -428,7 +428,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
     {
       size_t __old_len = __r->_M_size;
       _CharT* __new_data = (_CharT*)
-	_Data_allocate(_S_rounded_up_size(__old_len + __len));
+	_Rope_rep_base<_CharT, _Alloc>::_Data_allocate(_S_rounded_up_size(__old_len + __len));
       _RopeLeaf* __result;
 
       uninitialized_copy_n(__r->_M_data, __old_len, __new_data);
@@ -509,7 +509,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
 	    }
 	  __catch(...)
 	    {
-	      _C_deallocate(__result,1);
+	      rope::_C_deallocate(__result,1);
 	      __throw_exception_again;
 	    }
 	  // In case of exception, we need to deallocate
@@ -812,7 +812,7 @@ _GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)
 	    if (__result_len > __lazy_threshold)
 	      goto lazy;
 	    __section = (_CharT*)
-	      _Data_allocate(_S_rounded_up_size(__result_len));
+	      _Rope_rep_base<_CharT, _Alloc>::_Data_allocate(_S_rounded_up_size(__result_len));
 	    __try
 	      {	(*(__f->_M_fn))(__start, __result_len, __section); }
 	    __catch(...)
