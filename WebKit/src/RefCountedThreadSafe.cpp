#include "RefCountedThreadSafe.h"

template<class T>
RefCountedThreadSafe<T>::RefCountedThreadSafe(){}

template<class T>
void RefCountedThreadSafe::deref(){
    if (derefBase())
    {
        delete static_cast<T*>(this);
    }
}