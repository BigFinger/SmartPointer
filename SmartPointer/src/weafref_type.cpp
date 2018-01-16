#pragma once
#include <windows.h>
#include "weakref_type.h"
#include "weakref_impl.h"

RefBase* weakref_type::refBase() const{
	return static_cast<const weakref_impl*>(this)->mBase;
}

void weakref_type::incWeak(const void* id){
	weakref_impl* const impl = static_cast<weakref_impl*>(this);
	impl->addWeakRef(id);
	const int oldValue = InterlockedExchangeAdd((volatile LONG*)&impl->mWeak, 1);
	LOG_ASSERT(oldValue >= 0. "incWeak called on %p after last weak ref", this);
}

void weakref_type::decWeak(const void* id){
	weakref_impl* const impl = static_cast<weakref_impl*>(this);
	impl->removeWeakRef(id);
	const int oldValue = InterlockedExchangeAdd((volatile LONG*)&impl->mWeak, -1);
	LOG_ASSERT(oldValue >= 0. "incWeak called on %p after last weak ref", this);
	if (oldValue == 1)
	{
		if ((impl->mFlags&RefBase::OBJECT_LIFETIME_WEAK) != RefBase::OBJECT_LIFETIME_WEAK)
		{
			if (impl->mStrong == INITIAL_STRONG_VALUE)
			{
				delete impl->mBase;
			}
			else
			{
				delete impl;
			}
		}
		else
		{

		}
	}
}