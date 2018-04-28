#include "RefCountedThreadSafeBase.h"
#include "windows.h"

RefCountedThreadSafeBase::RefCountedThreadSafeBase(int initialRefCount /* = 1 */):m_refCount(initialRefCount){}

void RefCountedThreadSafeBase::ref(){
    long volatile* element = reinterpret_cast<long volatile*>(&m_refCount);
    InterlockedIncrement(element);
}

bool RefCountedThreadSafeBase::hasOneRef() const{
    bool result = false;
    int refCount = this->refCount();
    if (refCount == 1)
    {
        result = true;
    }
    return result;
}

int RefCountedThreadSafeBase::refCount() const{
    return static_cast<int const volatile &>(m_refCount);
}

bool RefCountedThreadSafeBase::derefBase(){
    long volatile* element = reinterpret_cast<long volatile*>(&m_refCount);
    InterlockedDecrement(element);
    if (element <= 0)
    {
        return true;
    }
    return false;
}