#pragma once
#include "config.h"

class SMART_POINTER_EXPORT RefCountedBase{
public:
    bool hasOneRef() const;
    void ref();
    int refCount() const;
protected:
    RefCountedBase();
    ~RefCountedBase();
protected:
    bool derefBase();
    bool deletionHasBegun() const;
private:
    friend void adopted(RefCountedBase*);
    int m_refCount;
    bool m_deletionHasBegun;
    bool m_adoptionIsRequired;
};