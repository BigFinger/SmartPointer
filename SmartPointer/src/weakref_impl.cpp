#include "weakref_impl.h"

weakref_impl::weakref_impl(RefBase* base):
    mStrong(INITIAL_STRONG_VALUE),
    mWeak(0),
    mBase(base),
    mFlags(0){}

void weakref_impl::addStrongRef(const void* id){}

void weakref_impl::removeStrongRef(const void* id){}

void weakref_impl::addWeakRef(const void* id){}

void weakref_impl::removeWeakRef(const void* id){}

void weakref_impl::printRefs() const {}

void weakref_impl::trackMe(bool track, bool retain){}