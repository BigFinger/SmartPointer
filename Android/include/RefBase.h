#pragma once
#include <iostream>
#include "config.h"
#include "weakref_impl.h"
using namespace std;

class SMART_POINTER_EXPORT RefBase{
public:
    void incStrong(const void* id) const;
    void decStrong(const void* id) const;
    void forceIncStrong(const void* id) const;
    int getStrongCount() const;
public:
    weakref_type* createWeak(const void* id) const;
    weakref_type* getWeakRefs() const;
    inline void printRefs() const;
    inline void trackMe(bool enable, bool retain);
protected:
    RefBase();
    virtual ~RefBase();
    void extendObjectLifetime(int mode);
    virtual void onFirstRef();
    virtual void onLastStrongRef(const void* id);
    /* 控制是否允许被强引用 */
    virtual bool onIncStrongAttempted(unsigned int flags, const void* id);
    virtual void onLastWeakRef(const void* id);
    enum 
    {
        OBJECT_LIFETIME_WEAK = 0X0001,          /* 受弱引用计数控制 */
        OBJECT_LIFETIME_FOREVER = 0X0003        /* 生命周期既不受强引用控制，也不受弱引用控制，谁new谁delete */
    };
    enum
    {
        FIRST_INC_STRONG = 0x0001
    };
private:
    friend class weakref_type;
    RefBase(const RefBase& o);
    RefBase& operator = (const RefBase& o);
    weakref_impl* const mRefs;
};