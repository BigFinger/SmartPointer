#pragma once
#include <windows.h>
#include "weakref_type.h"
#include "weakref_impl.h"

RefBase* weakref_type::refBase() const{
    return static_cast<const weakref_impl*>(this)->mBase;
}

void weakref_type::incWeak(const void* id){
    weakref_impl* const impl = static_cast<weakref_impl*>(this);
    impl->addWeakRef(id);
    const int oldValue = InterlockedExchangeAdd((volatile LONG*)&impl->mWeak, 1);
    LOG_ASSERT(oldValue >= 0. "incWeak called on %p after last weak ref", this);
}

void weakref_type::decWeak(const void* id){
    weakref_impl* const impl = static_cast<weakref_impl*>(this);
    impl->removeWeakRef(id);
    const int oldValue = InterlockedExchangeAdd((volatile LONG*)&impl->mWeak, -1);
    LOG_ASSERT(oldValue >= 0. "incWeak called on %p after last weak ref", this);
    if (oldValue == 1)
    {
        if ((impl->mFlags & RefBase::OBJECT_LIFETIME_WEAK) != RefBase::OBJECT_LIFETIME_WEAK)
        {
            if (impl->mStrong == INITIAL_STRONG_VALUE)
            {
                delete impl->mBase;
            }
            else
            {
                delete impl;
            }
        }
        else
        {
            impl->mBase->onLastWeakRef(id);
            if ((impl->mFlags & RefBase::OBJECT_LIFETIME_FOREVER) != RefBase::OBJECT_LIFETIME_FOREVER)
            {
                delete impl->mBase;
            }
        }
    }
}

bool weakref_type::attemptIncStrong(const void* id){
    incWeak(id);
    weakref_impl* const impl = static_cast<weakref_impl*>(this);
    int curCount = impl->mStrong;
    LOG_ASSERT(curCount >= 0, "attemptIncStrong called on %p after underflow", this);
    while(curCount > 0 && curCount != INITIAL_STRONG_VALUE)
    {
        if (InterlockedCompareExchange((unsigned int*)&impl->mStrong, curCount, curCount + 1) == curCount)
        {
            break;
        }
        curCount = impl->mStrong;
    }
    if (curCount <= 0 || curCount == INITIAL_STRONG_VALUE)
    {
        bool allow = false;
        if (curCount == INITIAL_STRONG_VALUE)
        {
            allow = (impl->mFlags & RefBase::OBJECT_LIFETIME_WEAK) != RefBase::OBJECT_LIFETIME_WEAK 
                || impl->mBase->onIncStrongAttempted(RefBase::FIRST_INC_STRONG, id);
        }
        else
        {
            allow = (impl->mFlags & RefBase::OBJECT_LIFETIME_WEAK) == RefBase::OBJECT_LIFETIME_WEAK 
                && impl->mBase->onIncStrongAttempted(RefBase::FIRST_INC_STRONG, id);
        }
        if (!allow)
        {
            decWeak(id);
            return false;
        }
        curCount = InterlockedExchangeAdd((volatile LONG*)&impl->mStrong, 1);
        if (curCount > 0 && curCount < INITIAL_STRONG_VALUE)
        {
            impl->mBase->onLastStrongRef(id);
        }
    }
    impl->addWeakRef(id);
    impl->addStrongRef(id);
    if (curCount == INITIAL_STRONG_VALUE)
    {
        InterlockedExchangeAdd((volatile LONG*)&impl->mStrong, -INITIAL_STRONG_VALUE);
        impl->mBase->onFirstRef();
    }
    return true;
}

bool weakref_type::attemptIncWeak(const void* id){
    weakref_impl* const impl = static_cast<weakref_impl*>(this);
    int curCount = impl->mWeak;
    LOG_ASSERT(curCount >= 0, "attemptIncWeak called ont %p after underflow", this);
    while(curCount > 0)
    {
        if (curCount == InterlockedCompareExchange((unsigned long*)&impl->mWeak, curCount, curCount + 1))
        {
            break;
        }
        curCount = impl->mWeak;
    }
    if (curCount > 0)
    {
        impl->addWeakRef(id);
    }
    return curCount > 0;
}

int weakref_type::getWeakCount() const{
    return static_cast<weakref_impl*>(this)->mWeak;
}

void weakref_type::printRefs() const{
    static_cast<weakref_impl*>(this)->printRefs();
}

void weakref_type::trackMe(bool enable, bool retain){
    static_cast<weakref_impl*>(this)->trackMe(enable, retain);
}
