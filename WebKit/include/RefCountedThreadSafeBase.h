#pragma once
#include "config.h"

class SMART_POINTER_EXPORT RefCountedThreadSafeBase{
public:
    RefCountedThreadSafeBase(int initialRefCount = 1);
    ~RefCountedThreadSafeBase();

public:
    void ref();
    bool hasOneRef() const;
    int refCount() const;
protected:
    bool derefBase();
private:
    int m_refCount;
};

