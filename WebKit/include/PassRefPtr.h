#include "config.h"

template<class T>
class PassRefPtr{
public:
    PassRefPtr();
    PassRefPtr(std::nullptr_t);
    PassRefPtr(T* ptr);
    explicit PassRefPtr(T& ptr);
    PassRefPtr(const PassRefPtr& o);
    ~PassRefPtr();
public:
    T* get() const;
    T* leakRef() const;
    T& operator*() const;
    T* operator-> () const;
    bool operator! () const;
    friend PassRefPtr adoptRef<T>(T*);
private:
    enum AdoptRefTag{AdoptRef};
    PassRefPtr(T* ptr, AdoptRefTag);
private:
    PassRefPtr& operator=(const PassRefPtr&);
private:
    mutable T* m_ptr;
};

template<class T>
PassRefPtr<T>::PassRefPtr():m_ptr(NULL){}

template<class T>
PassRefPtr<T>::PassRefPtr(std::nullptr_t):m_ptr(NULL){}

template<class T>
PassRefPtr<T>::PassRefPtr(T* ptr):m_ptr(ptr){
    refIfNotNull(ptr);
}

template<class T>
explicit PassRefPtr<T>::PassRefPtr(T& ptr):m_ptr(&ptr){
    m_ptr->ref();
}

template<class T>
PassRefPtr<T>::PassRefPtr(const PassRefPtr& o):m_ptr(o.leakRef()){}

template<class T>
PassRefPtr<T>::~PassRefPtr(){
    derefIfNotNull(m_ptr);
}

template<class T>
PassRefPtr<T>::PassRefPtr(T* ptr, AdoptRefTag):m_ptr(ptr){}

template<class T>
T* PassRefPtr<T>::get() const{
    return m_ptr;
}

template<class T>
T* PassRefPtr<T>::leakRef() const{
    T* ptr = m_ptr;
    m_ptr = NULL;
    return ptr;
}

template<class T>
T& PassRefPtr<T>::operator*(){
    return *m_ptr;
}

template<class T>
T* PassRefPtr<T>::operator-> (){
    return m_ptr;
}

template<class T>
bool PassRefPtr<T>::operator! (){
    return !m_ptr;
}

template<class T>
T* PassRefPtr<T>::operator= const{
    return *this;
}

template<class T>
PassRefPtr<T> adoptRef(T* p){
    adopted(p);
    return PassRefPtr<T>(p, PassRefPtr<T>::AdoptRef);
}