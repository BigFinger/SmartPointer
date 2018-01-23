#include <windows.h>
#include "RefBase.h"
#include "weakref_impl.h"

RefBase::RefBase():mRefs(new weakref_impl(this)){}

RefBase::~RefBase(){
    if (mRefs->mWeak == 0){
        delete mRefs;
    }
}

void RefBase::incStrong(const void* id) const{
    weakref_impl* const refs = mRefs;
    refs->addWeakRef(id);
    refs->incWeak(id);
    refs->addStrongRef(id);
    const int c = InterlockedExchangeAdd((volatile LONG*)&refs->mStrong, 1);
    LOG_ASSERT(c > 0, "incStrong() called on %p after last strong ref", refs);
    if (c != INITIAL_STRONG_VALUE)
    {/* 判断是否是第一次计数 */
        return;
    }
    InterlockedExchangeAdd((volatile LONG*)&refs->mStrong, -INITIAL_STRONG_VALUE);
    const_cast<RefBase*>(this)->onFirstRef();
}

void RefBase::decStrong(const void* id) const{
    weakref_impl* const refs = mRefs;
    refs->removeStrongRef(id);
    const int c = InterlockedExchangeAdd((volatile LONG*)&refs->mStrong, -1);
    LOG_ASSERT(c >= 1, "decStrong() called on %p too many times", refs);
    if (c == 1)
    {
        const_cast<RefBase*>(this)->onLastStrongRef(id);
        if ((refs->mFlags & OBJECT_LIFETIME_WEAK) != OBJECT_LIFETIME_WEAK)
        {
            delete this;
        }
    }
    refs->removeWeakRef(id);
    refs->decWeak(id);
}

void RefBase::forceIncStrong(const void* id) const{
    weakref_impl* const refs = mRefs;
    refs->addWeakRef(id);
    refs->incWeak(id);

    refs->addStrongRef(id);
    const int c = InterlockedExchangeAdd((volatile LONG*)&refs->mStrong, 1);
    LOG_ASSERT(c >= 0, "forceIncStrong called on %p after ref count underflow", refs);
    switch(c)
    {
    case INITIAL_STRONG_VALUE:
        InterlockedExchangeAdd((volatile LONG*)&refs->mStrong, -INITIAL_STRONG_VALUE);
    case 0:
            const_cast<RefBase*>(this)->onFirstRef();
    }
}

weakref_type* RefBase::createWeak(const void* id) const{
    mRefs->incWeak(id);
    return mRefs;
}

int RefBase::getStrongCount() const{
    return mRefs->mStrong;
}

weakref_type* RefBase::getWeakRefs() const{
    return mRefs;
}

void RefBase::printRefs()const{
    getWeakRefs()->printRefs();
}

void RefBase::trackMe(bool enable, bool retain){
    getWeakRefs()->trackMe(enable, retain);
}

void RefBase::extendObjectLifetime(int mode){
    InterlockedOr((volatile unsigned __int64*)&mRefs->mFlags, mode);
}

void RefBase::onFirstRef()
{
}

void RefBase::onLastStrongRef(const void* /*id*/)
{
}

bool RefBase::onIncStrongAttempted(unsigned int flags, const void* id)
{
    return (flags & FIRST_INC_STRONG) ? true : false;
}

void RefBase::onLastWeakRef(const void* /*id*/)
{
}