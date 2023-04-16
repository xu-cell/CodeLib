/* ************************************************************************
> File Name:     Sgi_Stl_MemPool.h
> Author:        程序员Sefr
> email:   2459811340@qq.com
> Created Time:  Sat 15 Apr 2023 08:29:55 PM CST
> Description:   
 ************************************************************************/

#include <cstdlib>
#include <stdio.h>
#include <mutex>
namespace mycodelib { 

class Alloc {

 private:
  enum { ALIGN = 8 };
  enum { MAX_BYTES = 128 };
  enum { NFREELISTS = 16 };
  
  static size_t S_round_up(size_t bytes) {

  }

 public:
  union Obj {
    union Obj* M_free_list_link;
    char M_client_data[1];
  };
 public:
  static Obj* volatile S_free_list_[NFREELISTS];
  
  static size_t S_freelist_index(size_t bytes) {

  }

  static void* S_refill(size_t n);
  static char* S_chunk_alloc(size_t size, int& nobjs);

  static void* allocate(size_t n) {

  }

  static void deallocate(void*p, size_t n) {

  }

  static void* reallocate(void*p, size_t old_sz, size_t new_sz);

  static char* S_start_free_;
  static char* S_end_free_;
  static size_t S_heap_size_;
};



char* Alloc::S_chunk_alloc(size_t size, int& nobjs) {

}

void* Alloc::S_refill(size_t n) {

}

void* Alloc::reallocate(void*p, size_t old_size, size_t new_size) {

}

char* Alloc::S_start_free_ = 0;
char* Alloc::S_end_free_ = 0;
size_t Alloc::S_heap_size_ = 0;
typename Alloc::Obj* volatile  S_free_list_[NFREELISTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };


} // namespace mycodelib


// # ifdef __USE_MALLOC

// typedef malloc_alloc alloc;
// typedef malloc_alloc single_client_alloc;

// # else


// // Default node allocator.
// // With a reasonable compiler, this should be roughly as fast as the
// // original STL class-specific allocators, but with less fragmentation.
// // Default_alloc_template parameters are experimental and MAY
// // DISAPPEAR in the future.  Clients should just use alloc for now.
// //
// // Important implementation properties:
// // 1. If the client request an object of size > _MAX_BYTES, the resulting
// //    object will be obtained directly from malloc.
// // 2. In all other cases, we allocate an object of size exactly
// //    _S_round_up(requested_size).  Thus the client has enough size
// //    information that we can return the object to the proper free list
// //    without permanently losing part of the object.
// //

// // The first template parameter specifies whether more than one thread
// // may use this allocator.  It is safe to allocate an object from
// // one instance of a default_alloc and deallocate it with another
// // one.  This effectively transfers its ownership to the second one.
// // This may have undesirable effects on reference locality.
// // The second parameter is unreferenced and serves only to allow the
// // creation of multiple default_alloc instances.
// // Node that containers built on different allocator instances have
// // different types, limiting the utility of this approach.

// #if defined(__SUNPRO_CC) || defined(__GNUC__)
// // breaks if we make these template class members:
//   enum {_ALIGN = 8};
//   enum {_MAX_BYTES = 128};
//   enum {_NFREELISTS = 16}; // _MAX_BYTES/_ALIGN
// #endif

// template <bool threads, int inst>
// class __default_alloc_template {

// private:
//   // Really we should use static const int x = N
//   // instead of enum { x = N }, but few compilers accept the former.
// #if ! (defined(__SUNPRO_CC) || defined(__GNUC__))
//     enum {_ALIGN = 8};
//     enum {_MAX_BYTES = 128};
//     enum {_NFREELISTS = 16}; // _MAX_BYTES/_ALIGN
// # endif
//   static size_t
//   _S_round_up(size_t __bytes) 
//     { return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }

// __PRIVATE:
//   union _Obj {
//         union _Obj* _M_free_list_link;
//         char _M_client_data[1];    /* The client sees this.        */
//   }; 
// private:
// # if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
//     static _Obj* __STL_VOLATILE _S_free_list[]; 
//         // Specifying a size results in duplicate def for 4.1
// # else
//     static _Obj* __STL_VOLATILE _S_free_list[_NFREELISTS]; 
// # endif
//   static  size_t _S_freelist_index(size_t __bytes) {
//         return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
//   }

//   // Returns an object of size __n, and optionally adds to size __n free list.
//   static void* _S_refill(size_t __n);
//   // Allocates a chunk for nobjs of size size.  nobjs may be reduced
//   // if it is inconvenient to allocate the requested number.
//   static char* _S_chunk_alloc(size_t __size, int& __nobjs);

//   // Chunk allocation state.
//   static char* _S_start_free;
//   static char* _S_end_free;
//   static size_t _S_heap_size;

// # ifdef __STL_THREADS
//     static _STL_mutex_lock _S_node_allocator_lock;
// # endif

//     // It would be nice to use _STL_auto_lock here.  But we
//     // don't need the NULL check.  And we do need a test whether
//     // threads have actually been started.
//     class _Lock;
//     friend class _Lock;
//     class _Lock {
//         public:
//             _Lock() { __NODE_ALLOCATOR_LOCK; }
//             ~_Lock() { __NODE_ALLOCATOR_UNLOCK; }
//     };

// public:

//   /* __n must be > 0      */
//   static void* allocate(size_t __n)
//   {
//     void* __ret = 0;

//     if (__n > (size_t) _MAX_BYTES) {
//       __ret = malloc_alloc::allocate(__n);
//     }
//     else {
//       _Obj* __STL_VOLATILE* __my_free_list
//           = _S_free_list + _S_freelist_index(__n);
//       // Acquire the lock here with a constructor call.
//       // This ensures that it is released in exit or during stack
//       // unwinding.
// #     ifndef _NOTHREADS
//       /*REFERENCED*/
//       _Lock __lock_instance;
// #     endif
//       _Obj* __RESTRICT __result = *__my_free_list;
//       if (__result == 0)
//         __ret = _S_refill(_S_round_up(__n));
//       else {
//         *__my_free_list = __result -> _M_free_list_link;
//         __ret = __result;
//       }
//     }

//     return __ret;
//   };

//   /* __p may not be 0 */
//   static void deallocate(void* __p, size_t __n)
//   {
//     if (__n > (size_t) _MAX_BYTES)
//       malloc_alloc::deallocate(__p, __n);
//     else {
//       _Obj* __STL_VOLATILE*  __my_free_list
//           = _S_free_list + _S_freelist_index(__n);
//       _Obj* __q = (_Obj*)__p;

//       // acquire lock
// #       ifndef _NOTHREADS
//       /*REFERENCED*/
//       _Lock __lock_instance;
// #       endif /* _NOTHREADS */
//       __q -> _M_free_list_link = *__my_free_list;
//       *__my_free_list = __q;
//       // lock is released here
//     }
//   }

//   static void* reallocate(void* __p, size_t __old_sz, size_t __new_sz);

// } ;

// typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
// typedef __default_alloc_template<false, 0> single_client_alloc;

// template <bool __threads, int __inst>
// inline bool operator==(const __default_alloc_template<__threads, __inst>&,
//                        const __default_alloc_template<__threads, __inst>&)
// {
//   return true;
// }

// # ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
// template <bool __threads, int __inst>
// inline bool operator!=(const __default_alloc_template<__threads, __inst>&,
//                        const __default_alloc_template<__threads, __inst>&)
// {
//   return false;
// }
// # endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */



// /* We allocate memory in large chunks in order to avoid fragmenting     */
// /* the malloc heap too much.                                            */
// /* We assume that size is properly aligned.                             */
// /* We hold the allocation lock.                                         */
// template <bool __threads, int __inst>
// char*
// __default_alloc_template<__threads, __inst>::_S_chunk_alloc(size_t __size, 
//                                                             int& __nobjs)
// {
//     char* __result;
//     size_t __total_bytes = __size * __nobjs;
//     size_t __bytes_left = _S_end_free - _S_start_free;

//     if (__bytes_left >= __total_bytes) {
//         __result = _S_start_free;
//         _S_start_free += __total_bytes;
//         return(__result);
//     } else if (__bytes_left >= __size) {
//         __nobjs = (int)(__bytes_left/__size);
//         __total_bytes = __size * __nobjs;
//         __result = _S_start_free;
//         _S_start_free += __total_bytes;
//         return(__result);
//     } else {
//         size_t __bytes_to_get = 
// 	  2 * __total_bytes + _S_round_up(_S_heap_size >> 4);
//         // Try to make use of the left-over piece.
//         if (__bytes_left > 0) {
//             _Obj* __STL_VOLATILE* __my_free_list =
//                         _S_free_list + _S_freelist_index(__bytes_left);

//             ((_Obj*)_S_start_free) -> _M_free_list_link = *__my_free_list;
//             *__my_free_list = (_Obj*)_S_start_free;
//         }
//         _S_start_free = (char*)malloc(__bytes_to_get);
//         if (0 == _S_start_free) {
//             size_t __i;
//             _Obj* __STL_VOLATILE* __my_free_list;
// 	    _Obj* __p;
//             // Try to make do with what we have.  That can't
//             // hurt.  We do not try smaller requests, since that tends
//             // to result in disaster on multi-process machines.
//             for (__i = __size;
//                  __i <= (size_t) _MAX_BYTES;
//                  __i += (size_t) _ALIGN) {
//                 __my_free_list = _S_free_list + _S_freelist_index(__i);
//                 __p = *__my_free_list;
//                 if (0 != __p) {
//                     *__my_free_list = __p -> _M_free_list_link;
//                     _S_start_free = (char*)__p;
//                     _S_end_free = _S_start_free + __i;
//                     return(_S_chunk_alloc(__size, __nobjs));
//                     // Any leftover piece will eventually make it to the
//                     // right free list.
//                 }
//             }
// 	    _S_end_free = 0;	// In case of exception.
//             _S_start_free = (char*)malloc_alloc::allocate(__bytes_to_get);
//             // This should either throw an
//             // exception or remedy the situation.  Thus we assume it
//             // succeeded.
//         }
//         _S_heap_size += __bytes_to_get;
//         _S_end_free = _S_start_free + __bytes_to_get;
//         return(_S_chunk_alloc(__size, __nobjs));
//     }
// }


// /* Returns an object of size __n, and optionally adds to size __n free list.*/
// /* We assume that __n is properly aligned.                                */
// /* We hold the allocation lock.                                         */
// template <bool __threads, int __inst>
// void*
// __default_alloc_template<__threads, __inst>::_S_refill(size_t __n)
// {
//     int __nobjs = 20;
//     char* __chunk = _S_chunk_alloc(__n, __nobjs);
//     _Obj* __STL_VOLATILE* __my_free_list;
//     _Obj* __result;
//     _Obj* __current_obj;
//     _Obj* __next_obj;
//     int __i;

//     if (1 == __nobjs) return(__chunk);
//     __my_free_list = _S_free_list + _S_freelist_index(__n);

//     /* Build free list in chunk */
//       __result = (_Obj*)__chunk;
//       *__my_free_list = __next_obj = (_Obj*)(__chunk + __n);
//       for (__i = 1; ; __i++) {
//         __current_obj = __next_obj;
//         __next_obj = (_Obj*)((char*)__next_obj + __n);
//         if (__nobjs - 1 == __i) {
//             __current_obj -> _M_free_list_link = 0;
//             break;
//         } else {
//             __current_obj -> _M_free_list_link = __next_obj;
//         }
//       }
//     return(__result);
// }

// template <bool threads, int inst>
// void*
// __default_alloc_template<threads, inst>::reallocate(void* __p,
//                                                     size_t __old_sz,
//                                                     size_t __new_sz)
// {
//     void* __result;
//     size_t __copy_sz;

//     if (__old_sz > (size_t) _MAX_BYTES && __new_sz > (size_t) _MAX_BYTES) {
//         return(realloc(__p, __new_sz));
//     }
//     if (_S_round_up(__old_sz) == _S_round_up(__new_sz)) return(__p);
//     __result = allocate(__new_sz);
//     __copy_sz = __new_sz > __old_sz? __old_sz : __new_sz;
//     memcpy(__result, __p, __copy_sz);
//     deallocate(__p, __old_sz);
//     return(__result);
// }

// #ifdef __STL_THREADS
//     template <bool __threads, int __inst>
//     _STL_mutex_lock
//     __default_alloc_template<__threads, __inst>::_S_node_allocator_lock
//         __STL_MUTEX_INITIALIZER;
// #endif

// template <bool __threads, int __inst>
// char* __default_alloc_template<__threads, __inst>::_S_start_free = 0;

// template <bool __threads, int __inst>
// char* __default_alloc_template<__threads, __inst>::_S_end_free = 0;

// template <bool __threads, int __inst>
// size_t __default_alloc_template<__threads, __inst>::_S_heap_size = 0;

// template <bool __threads, int __inst>
// typename __default_alloc_template<__threads, __inst>::_Obj* __STL_VOLATILE
// __default_alloc_template<__threads, __inst> ::_S_free_list[
// # if defined(__SUNPRO_CC) || defined(__GNUC__) || defined(__HP_aCC)
//     _NFREELISTS
// # else
//     __default_alloc_template<__threads, __inst>::_NFREELISTS
// # endif
// ] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
// // The 16 zeros are necessary to make version 4.1 of the SunPro
// // compiler happy.  Otherwise it appears to allocate too little
// // space for the array.

// #endif /* ! __USE_MALLOC */



