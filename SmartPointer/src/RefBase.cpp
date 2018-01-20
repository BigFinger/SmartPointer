#include "RefBase.h"
#include "weakref_impl.h"

RefBase::RefBase():mRefs(new weakref_impl(this)){}

RefBase::~RefBase(){
    if (mRefs->mWeak == 0){
        delete mRefs;
    }
}

weakref_type* RefBase::createWeak(const void* id) const{
    mRefs->incWeak(id);
    return mRefs;
}