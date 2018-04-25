#pragma once

class SMART_POINTER_EXPORT RefCountedThreadSafeBase{
public:
    bool hasOneRef() const;

protected:
    RefCountedThreadSafeBase();
    ~RefCountedThreadSafeBase();

protected:
    void addRef() const;
    bool release() const;

private:
    mutable int ref_count_;
    mutable bool in_dtor_;
};