#pragma once
#include "RefBase.h"
#include "weakref_type.h"

template<class T>
class RefCountPtr{
public:
    RefCountPtr();
    RefCountPtr(T* other);
    RefCountPtr(const RefCountPtr<T>& other);
    template<class U>
    RefCountPtr(U* other);
    template<class U>
    RefCountPtr(const RefCountPtr<U>& other);
    ~RefCountPtr();
public:
    RefCountPtr& operator = (T& other);
    RefCountPtr& operator = (const RefCountPtr<T>& other);
    template<class U>
    RefCountPtr& operator = (const RefCountPtr<U>& other);
    template<class U>
    RefCountPtr& operator = (U* other);
    T& operator*() const;
    T* operator->() const;
    T* get() const;

    void force_set(T* other);
    void clear();
};