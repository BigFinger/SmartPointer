#pragma once
#include "config.h"

template <typename T>
class RefCountWeakPtr{
public:
    typedef typename RefBase::weakref_type weakref_type;

    RefCountWeakPtr();

    RefCountWeakPtr(T* other);
    RefCountWeakPtr(const RefCountWeakPtr<T>& other);
    RefCountWeakPtr(const RefCountPtr<T>& other);
    template<typename U> 
    RefCountWeakPtr(U* other);
    template<typename U>
    RefCountWeakPtr(const RefCountPtr<U>& other);
    template<typename U> 
    RefCountWeakPtr(const RefCountWeakPtr<U>& other);

    ~RefCountWeakPtr();

    RefCountWeakPtr& operator = (T* other);
    RefCountWeakPtr& operator = (const RefCountWeakPtr<T>& other);
    RefCountWeakPtr& operator = (const RefCountPtr<T>& other);

    template<typename U> 
    RefCountWeakPtr& operator = (U* other);
    template<typename U> 
    RefCountWeakPtr& operator = (const RefCountWeakPtr<U>& other);
    template<typename U> 
    RefCountWeakPtr& operator = (const RefCountPtr<U>& other);

    void set_object_and_refs(T* other, weakref_type* refs);

    RefCountPtr<T> 
    promote() const;

    void clear();

    weakref_type* get_refs() const;

    T* unsafe_get() const;

    COMPARE(== )
        COMPARE(!= )
        COMPARE(> )
        COMPARE(< )
        COMPARE(<= )
        COMPARE(>= )

private:
    template<typename Y> 
    friend class sp;
    template<typename Y> 
    friend class wp;

    T*              m_ptr;
    weakref_type*   m_refs;
};

template<typename T>
RefCountWeakPtr<T>::RefCountWeakPtr():m_ptr(0){}

template<typename T>
RefCountWeakPtr<T>::RefCountWeakPtr(T* other):m_ptr(other)
{
    if (other != NULL)
    {
        m_refs = other->createWeak(this);
    }
}

template<typename T>
RefCountWeakPtr<T>::RefCountWeakPtr(const RefCountWeakPtr<T>& other):m_ptr(other.m_ptr), m_refs(other.m_refs)
{
    if (m_ptr != NULL)
    {
        m_refs->incWeak(this);
    }
}

template<typename T>
RefCountWeakPtr<T>::RefCountWeakPtr(const RefCountPtr<T>& other):m_ptr(other.m_ptr)
{
    if (m_ptr != NULL) 
    {
        m_refs = m_ptr->createWeak(this);
    }
}

template<typename T> 
template<typename U>
RefCountWeakPtr<T>::RefCountWeakPtr(U* other):m_ptr(other)
{
    if (other != NULL)
    {
        m_refs = other->createWeak(this);
    }
}

template<typename T> 
template<typename U>
RefCountWeakPtr<T>::RefCountWeakPtr(const RefCountWeakPtr<U>& other):m_ptr(other.m_ptr)
{
    if (m_ptr != NULL)
    {
        m_refs = other.m_refs;
        m_refs->incWeak(this);
    }
}

template<typename T> 
template<typename U>
RefCountWeakPtr<T>::RefCountWeakPtr(const RefCountPtr<U>& other):m_ptr(other.m_ptr)
{
    if (m_ptr != NULL)
    {
        m_refs = m_ptr->createWeak(this);
    }
}

template<typename T>
RefCountWeakPtr<T>::~RefCountWeakPtr()
{
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
    }
}

template<typename T>
RefCountWeakPtr<T>& RefCountWeakPtr<T>::operator = (T* other)
{
    weakref_type* newRefs = other ? other->createWeak(this) : 0;
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
    }
    m_ptr = other;
    m_refs = newRefs;
    return *this;
}

template<typename T>
RefCountWeakPtr<T>& RefCountWeakPtr<T>::operator = (const RefCountWeakPtr<T>& other)
{
    if (other.m_ptr != NULL)
    {
        other.m_refs->incWeak(this);
    }
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
    }
    m_ptr = other.m_ptr;
    m_refs = other.m_refs;
    return *this;
}

template<typename T>
RefCountWeakPtr<T>& RefCountWeakPtr<T>::operator = (const RefCountPtr<T>& other)
{
    weakref_type* newRefs = other != NULL ? other->createWeak(this) : 0;
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
    }
    m_ptr = other.get();
    m_refs = newRefs;
    return *this;
}

template<typename T> 
template<typename U>
RefCountWeakPtr<T>& RefCountWeakPtr<T>::operator = (U* other)
{
    weakref_type* newRefs = other ? other->createWeak(this) : 0;
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
    }
    m_ptr = other;
    m_refs = newRefs;
    return *this;
}

template<typename T> 
template<typename U>
RefCountWeakPtr<T>& RefCountWeakPtr<T>::operator = (const RefCountWeakPtr<U>& other)
{
    if (other.m_ptr != NULL)
    {
        other.m_refs->incWeak(this);
    }
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
    }
    m_ptr = other.m_ptr;
    m_refs = other.m_refs;
    return *this;
}

template<typename T> 
template<typename U>
RefCountWeakPtr<T>& RefCountWeakPtr<T>::operator = (const RefCountPtr<U>& other)
{
    weakref_type* newRefs = other != NULL ? other->createWeak(this) : 0;
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
    }
    m_ptr = other.get();
    m_refs = newRefs;
    return *this;
}

template<typename T>
void RefCountWeakPtr<T>::set_object_and_refs(T* other, weakref_type* refs)
{
    if (other != NULL)
    {
        refs->incWeak(this);
    }
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
    }
    m_ptr = other;
    m_refs = refs;
}

template<typename T>
RefCountPtr<T> RefCountWeakPtr<T>::promote() const
{
    return RefCountPtr<T>(m_ptr, m_refs);
}

template<typename T>
void RefCountWeakPtr<T>::clear()
{
    if (m_ptr != NULL)
    {
        m_refs->decWeak(this);
        m_ptr = 0;
    }
}

template<typename T>
weakref_type* RefCountWeakPtr::get_refs() const {
    return m_refs; 
}

template<typename T>
T* RefCountWeakPtr::unsafe_get() const { 
    return m_ptr; 
}