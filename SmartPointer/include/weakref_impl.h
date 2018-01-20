#pragma once
#include "config.h"
#include "RefBase.h"
#include "weakref_type.h"

class weakref_impl:public weakref_type{
public:
    weakref_impl(RefBase* base);
    ~weakref_impl();
    void addStrongRef(const void* id);
    void removeStrongRef(const void* id);
    void addWeakRef(const void* id);
    void removeWeakRef(const void* id);
    void printRefs() const;
    void trackMe(bool track, bool retain);
public:
    volatile int mStrong;
    volatile int mWeak;
    volatile int mFlags;
    RefBase* const mBase;
};