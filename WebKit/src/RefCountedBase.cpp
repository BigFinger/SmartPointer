#include "RefCountedBase.h"

bool RefCountedBase::hasOneRef() const{
    if (m_refCount == 1)
    {
        return true;
    }
    return false;
}

int RefCountedBase::refCount() const{
    return m_refCount;
}

RefCountedBase::RefCountedBase():m_refCount(1),m_deletionHasBegun(false), m_adoptionIsRequired(true){}

RefCountedBase::~RefCountedBase(){}

void RefCountedBase::ref(){
    m_refCount++;
}

bool RefCountedBase::derefBase(){
    bool result = false;
    m_refCount--;
    if (m_refCount == 0)
    {/* 引用计数已经为0 */
        m_deletionHasBegun = result = true;
    }
    return result;
}

bool RefCountedBase::deletionHasBegun() const{
    return m_deletionHasBegun;
}

void adopted(RefCountedBase *object){
    if (object != NULL)
    {
        object->m_adoptionIsRequired = false;
    }
}
