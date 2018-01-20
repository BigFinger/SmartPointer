#pragma once
#include "config.h"

class weakref_type{
public:
    RefBase* refBase() const;
    void incWeak(const void* id);
    void decWeak(const void* id);
    bool attemptIncStrong(const void* id);
    bool attemptIncWeak(const void* id);
    int getWeakCount() const;
    void printRefs() const;
    void trackMe(bool enalbe, bool retain);
};