#include "RefCountedBase.h"

bool RefCountedBase::hasOneRef() const{
    if (ref_count_ == 1)
    {
        return true;
    }
    return false;
}

RefCountedBase::RefCountedBase():ref_count_(0),in_dtor_(false){}

RefCountedBase::~RefCountedBase(){}

void RefCountedBase::addRef() const{
    ref_count_++;
}

bool RefCountedBase::release() const{
    if (--ref_count_ == 0)
    {
        in_dtor_ = true;
    }
    else
    {
        in_dtor_ = false;
    }
    return in_dtor_;
}