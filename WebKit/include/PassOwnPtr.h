#include "config.h"

template<typename T> 
PassOwnPtr<T> adoptPtr(T*);
template<typename T> 
PassOwnPtr<T[]> adoptArrayPtr(T*);

template<typename T> 
class PassOwnPtr {
public:
    PassOwnPtr();
    PassOwnPtr(std::nullptr_t);
    PassOwnPtr(const PassOwnPtr& o);
    ~PassOwnPtr();
public:
    PassOwnPtr<T>& operator*();
    PassOwnPtr<T>* operator->();
    bool operator!();
public:
    PassOwnPtr<T>* get() const;
    PassOwnPtr<T>* leakPtr() const;
    operator UnspecifiedBoolType() const;
    template<typename U> 
    friend PassOwnPtr<U> adoptPtr(U*);
    template<typename U> 
    friend PassOwnPtr<U[]> adoptArrayPtr(U* ptr);
    template<typename U> 
    friend class OwnPtr;

private:
    explicit PassOwnPtr(PtrType ptr);
    mutable PtrType m_ptr;
};

template<class T>
PassOwnPtr<T>::PassOwnPtr():m_ptr(NULL){}

template<class T>
PassOwnPtr<T>::PassOwnPtr(std::nullptr_t):m_ptr(NULL){}

template<class T>
PassOwnPtr<T>::PassOwnPtr(const PassOwnPtr& o):m_ptr(o.leakPtr()){}

template<class T>
PassOwnPtr<T>::~PassOwnPtr(){
    delete m_ptr;
    m_ptr = NULL;
}

template<class T>
PassOwnPtr<T>& PassOwnPtr<T>::operator* (){
    return *m_ptr;
}

template<class T>
PassOwnPtr<T>& PassOwnPtr<T>::operator-> (){
    return m_ptr;
}

template<class T>
bool PassOwnPtr<T>::operator! (){
    return !m_ptr;
}

template<class T>
PassOwnPtr<T>*


