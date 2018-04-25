#pragma once
#include "config.h"

struct SMART_POINTER_EXPORT AsserterBase{
    virtual ~AsserterBase(){}
    virtual void warn() = 0;
};

struct SMART_POINTER_EXPORT DCheckAsserter : public AsserterBase{
    virtual ~DCheckAsserter(){}
    virtual void warn(){}
};

class SMART_POINTER_EXPORT ThreadCollisionWarner{
public:
    explicit ThreadCollisionWarner(AsserterBase* asserter = new DCheckAsserter()):
    valid_thread_id(0), counter(0), asserter_(asserter) {};
    ~ThreadCollisionWarner(){
        delete asserter_;
    }
};