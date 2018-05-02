#include "RefCountedThreadSafeBase.h"

template<class T>
class RefCountedThreadSafe: public RefCountedThreadSafeBase{
public:
    void deref();
protected:
    RefCountedThreadSafe();
};