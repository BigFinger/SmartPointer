#include <iostream>
#include "config.h"
#include "RefBase.h"
using namespace std;

class WeightClass : public RefBase{
public:
    void printRefCount(){
        int strong = getStrongCount();
        weakref_type* ref = getWeakRefs();
        printf("---------------------------------\n");
        printf("Strong Ref Count: %d.\n", (strong == INITIAL_STRONG_VALUE ? 0 : strong));
        printf("Weak Ref Count: %d.\n", ref->getWeakCount());
        printf("---------------------------------\n");
    }
};

class StrongClass : public WeightClass{
public:
    StrongClass(){
        printf("Construct StrongClass Object.\n");
    }
    virtual ~StrongClass(){
        printf("Destory StrongClass Object.\n");
    }
};

class WeakClass : public WeightClass  {  
public:  
    WeakClass(){
        extendObjectLifetime(OBJECT_LIFETIME_WEAK);  
        printf("Construct WeakClass Object.\n");  
    }  
    virtual ~WeakClass(){  
        printf("Destory WeakClass Object.\n");  
    }  
};  