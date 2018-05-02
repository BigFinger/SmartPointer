#include "RefCountedBase.h"

template<class T>
class RefCounted: public RefCountedBase{
public:
    void deref();
protected:
    RefCounted();
};

template<class T>
void RefCounted::deref(){
    if (derefBase())
    {
        delete static_cast<T*>(this);
    }
}

template<class T>
RefCounted::RefCounted(){}

