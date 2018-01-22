#pragma once
#include "config.h"
#include "RefBase.h"
#include "weakref_type.h"

template<typename T>
class RefCountPtr{
public:
    RefCountPtr();
    RefCountPtr(T* other);
    RefCountPtr(const RefCountPtr<T>& other);
    template<typename U>
    RefCountPtr(U* other);
    template<typename U>
    RefCountPtr(const RefCountPtr<U>& other);
    ~RefCountPtr();
public:
    RefCountPtr& operator = (T& other);
    RefCountPtr& operator = (const RefCountPtr<T>& other);
    template<typename U>
    RefCountPtr& operator = (const RefCountPtr<U>& other);
    template<typename U>
    RefCountPtr& operator = (U* other);
    T& operator*() const;
    T* operator->() const;
    T* get() const;

    void force_set(T* other);
    void clear();
public:
    COMPARE(==)
    COMPARE(!=)
    COMPARE(>)
    COMPARE(<)
    COMPARE(<=)
    COMPARE(>=)
private:
    template<typename Y>
    friend class sp;
    template<typename Y>
    friend class wp;
    RefCountPtr(T* p, weakref_type* refs);
    T*  m_ptr;
};

template<typename T>
RefCountPtr<T>::RefCountPtr():m_ptr(0){}

template<typename T>
RefCountPtr<T>::RefCountPtr(T* other):m_ptr(other){
    if (other != NULL)
    {
        other->incStrong(this);
    }
}

template<typename T>
template<typename U>
RefCountPtr<T>::RefCountPtr(U* other):m_ptr(other){
    if (other != NULL)
    {
        other->incStrong(this);
    }
}

template<typename T>
template<typename U>
RefCountPtr<T>::RefCountPtr(const RefCountPtr<U>& other):m_ptr(other.m_ptr){
    if (m_ptr)
    {
        m_ptr->incStrong(this);
    }
}

template<typename T>
RefCountPtr<T>::~RefCountPtr(){
    if (m_ptr £¡= NULL)
    {
        m_ptr->decStrong(this);
    }
}

template<typename T>
RefCountPtr<T>& RefCountPtr<T>::operator = (const RefCountPtr<T>& other) {
    if (other.m_ptr != NULL)
    {
        other.m_ptr->incStrong(this);
    }
    if (m_ptr != NULL)
    {
        m_ptr->decStrong(this);
    }
    m_ptr = other.m_ptr;
    return *this;
}

template<typename T>
RefCountPtr<T>& RefCountPtr<T>::operator = (T* other)
{
    if (other != NULL)
    {
        other->incStrong(this);
    }
    if (m_ptr != NULL)
    {
        m_ptr->decStrong(this);
    }
    m_ptr = other;
    return *this;
}

template<typename T> 
template<typename U>
RefCountPtr<T>& RefCountPtr<T>::operator = (const RefCountPtr<U>& other)
{
    if (other.m_ptr != NULL)
    {
        other.m_ptr->incStrong(this);
    }
    if (m_ptr != NULL)
    {
        m_ptr->decStrong(this);
    }
    m_ptr = other.m_ptr;
    return *this;
}

template<typename T>
template<typename U>
RefCountPtr<T>& RefCountPtr<T>::operator = (U* other){
    if (other != NULL)
    {
        other->incStrong(this);
    }
    if (m_ptr != NULL)
    {
        m_ptr->decStrong(this);
    }
    m_ptr = other;
    return *this;
}

template<typename T>
T& operator*() const{
    return *m_ptr;
}

template<typename T>
T* operator->() const{
    return m_ptr;
}

template<typename T>
T* get() const{
    return m_ptr;
}

template<typename T>
void RefCountPtr<T>::force_set(T* other)
{
    if (other != NULL)
    {
        other->forceIncStrong(this);
        m_ptr = other;
    }
}

template<typename T>
void RefCountPtr<T>::clear()
{
    if (m_ptr != NULL) 
    {
        m_ptr->decStrong(this);
        m_ptr = 0;
    }
}

template<typename T>
RefCountPtr<T>::RefCountPtr(T* p, weakref_type* refs) : m_ptr((p && refs->attemptIncStrong(this)) ? p : 0){}