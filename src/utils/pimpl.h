#ifndef PIMPL_H
#define PIMPL_H
 
#include <memory>
 
template<typename T>
class pimpl {
private:
    std::unique_ptr<T> m;
public:
    pimpl();
    template<typename ...Args> pimpl( Args&& ... );
    ~pimpl();
    T* operator->();
    T& operator*();
    const T* operator->() const;
    const T& operator*() const;
};
 
#define IMPLEMENTATION_MEMBER( impl )                                          \
     class Impl;                                                                \
     pimpl< Impl > impl

#endif
