#ifndef MY_LIB_NONCOPYALBE_H
#define MY_LIB_NONCOPYABLE_H

namespace mycodelib {

class noncopyable {
 public:
    noncopyable(const noncopyable&) = delete;

    void operator=(const noncopyable&) = delete;



 protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

}   // mycodelib


#endif  // MYLIB_NONCOPYABLE_H