/* ************************************************************************
> File Name:     Singleton.h
> Author:        程序员Sefr
> email:   2459811340@qq.com
> Created Time:  Fri 07 Apr 2023 06:46:41 PM CST
> Description:   
 ************************************************************************/

#ifndef MY_LIB_SINGLETON_H
#define MY_LIB_SINGLETON_H

#include <assert.h>
#include <pthread.h>
#include <stdlib.h> // aexit

#include "noncopyable.h"

namespace mycodelib {

template <typename T>
struct has_no_destory {
  template <typename C> static char test(decltype(&C::no_destroy));
  template <typename C> static int32_t test(...);
  const static bool value = sizeof(test<T>(0)) == 1;
};

template <typename T>
class Singleton : noncopyable {
 public:
  Singleton() = delete;
  ~Singleton() = delete;

  static T& instance() {
    pthread_once(&ponce_, &Singleton::init);
    assert(value_ != nullptr);
    return *value_;
  }
 private:
  static void init() {
    value_ = new T();
    if(!has_no_destory<T>::value) {
        ::atexit(destroy);
    }
  }

  static void destroy() {
    typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy;
    (void)dummy;

    delete value_;
    value_ = nullptr;
  }
 private:
  static pthread_once_t ponce_;
  static T* value_;

};

template <typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template <typename T>
T* Singleton<T>::value_ = nullptr;

}   // mycodelib   

#endif // MY_LIB_SINGLETON_H