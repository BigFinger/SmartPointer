#pragma once
#include "config.h"

class SMART_POINTER_EXPORT RefCountedBase{
public:
    bool hasOneRef() const;
    void ref();
protected:
    RefCountedBase();
    ~RefCountedBase();
    void addRef() const;
    bool release() const;
private:
    mutable bool in_dtor_;
    mutable int  ref_count_;
};