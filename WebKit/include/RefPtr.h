#include "RefCounted.h"
#include "PassRefPtr.h"

enum HashTableDeletedValueType 
{
    HashTableDeletedValue
};

template<class T>
void refIfNotNull(T* ptr){
    if (ptr != NULL)
    {
        ptr->ref();
    }
}

template<class T>
void derefIfNotNull(T* ptr){
    if (ptr != NULL)
    {
        ptr->deref();
    }
}

template<class T>
class RefPtr{
public:
    RefPtr();
    RefPtr(std::nullptr_t);
    RefPtr(T* ptr);
    explicit RefPtr(T& ref);
    RefPtr(const RefPtr& o);
    RefPtr(HashTableDeletedValueType);
    ~RefPtr();
public:
    bool isHashTableDeletedValue() const;
    T* get() const;
    void clear();
    PassRefPtr<T> release();
    void swap(RefPtr&);
    static T* hashTableDeletedValue();
public:
    T& operator*() const;
    T* operator->() const;
    bool operator!() const;
    typedef T* (RefPtr::*UnspecifiedBoolType);
    operator UnspecifiedBoolType() const;

    RefPtr& operator= (const RefPtr&);
    RefPtr& operator= (T* optr);
    RefPtr& operator= (const PassRefPtr<T>&);

    template<class U>
    RefPtr<T>& operator = (const RefPtr<U>&);
    template<class U>
    RefPtr<T>& operator = (const PassRefPtr<U>&);
private:
    T* m_ptr;
};

template<class T>
RefPtr<T>::RefPtr():m_ptr(NULL){}

template<class T>
RefPtr<T>::RefPtr(std::nullptr_t):m_ptr(NULL){}

template<class T>
RefPtr<T>::RefPtr(T* ptr):m_ptr(ptr){
    refIfNotNull(ptr);
}

template<class T>
explicit RefPtr<T>::RefPtr(T& ref):m_ptr(&ref){
    m_ptr->ref();
}

template<class T>
RefPtr<T>::RefPtr(const RefPtr& o):m_ptr(o.m_ptr){
    refIfNotNull(m_ptr);
}

template<class T>
RefPtr<T>::RefPtr(HashTableDeletedValueType):m_ptr(hashTableDeletedValue()){}

template<class T>
RefPtr<T>::~RefPtr(){
    derefIfNotNull(m_ptr);
}

template<class T>
bool RefPtr<T>::isHashTableDeletedValue() const{
    return m_ptr == hashTableDeletedValue();
}

template<class T>
T* RefPtr<T>::get() const{
    return m_ptr;
}

template<class T>
void RefPtr<T>::clear(){
    T* ptr = m_ptr;
    m_ptr = NULL;
    derefIfNotNull(ptr);
}

template<class T>
PassRefPtr<T> RefPtr<T>::release(){
    PassRefPtr<T> tmp = adoptRef(m_ptr);
    m_ptr = NULL;
    return tmp;
}

template<class T>
T& RefPtr<T>::operator*(){
    return *m_ptr;
}

template<class T>
T* RefPtr<T>::operator->(){
    return m_ptr;
}

template<class T>
bool RefPtr<T>::operator!(){
    return !m_ptr;
}

template<class T>
operator RefPtr<T>::UnspecifiedBoolType() const{
    return m_ptr ? &RefPtr::m_ptr : NULL;
}

template<class T>
RefPtr<T>& RefPtr<T>::operator= (const RefPtr& o){
    RefPtr ptr = o;
    swap(ptr);
    return *this;
}

template<class T>
RefPtr<T>& RefPtr<T>::operator= (T* optr){
    RefPtr ptr = optr;
    swap(ptr);
    return *this;
}

template<class T>
RefPtr<T>& RefPtr<T>::operator=(const PassRefPtr<T>& o){
    RefPtr ptr = o;
    swap(ptr);
    return *this;
}

template<class T>
template<class U>
RefPtr<T>& RefPtr<T>::operator=(const RefPtr<U>& o){
    RefPtr ptr = o;
    swap(ptr);
    return *this;
}

template<class T>
template<class U>
RefPtr<T>& RefPtr<T>::operator=(const PassRefPtr<U>& o){
    RefPtr ptr = o;
    swap(ptr);
    return *this;
}

template<class T>
void RefPtr<T>::swap(RefPtr& o){
    std::swap(m_ptr, o.m_ptr);
}

template<class T>
static T* RefPtr<T>::hashTableDeletedValue(){
    return reinterpret_cast<T*>(-1);
}