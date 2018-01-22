#pragma once

#define SMART_POINTER_EXPORT  _declspec(dllexport)
#define LOG_ASSERT(a,b,c)
#define INITIAL_STRONG_VALUE (1 << 28)

#define COMPARE(_op_)                                           \
    inline bool operator _op_ (const RefCountPtr<T>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
    inline bool operator _op_ (const RefCountWeakPtr<T>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
    inline bool operator _op_ (const T* o) const {                  \
    return m_ptr _op_ o;                                        \
}                                                               \
    template<typename U>                                            \
    inline bool operator _op_ (const RefCountPtr<U>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
    template<typename U>                                            \
    inline bool operator _op_ (const RefCountWeakPtr<U>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
    template<typename U>                                            \
    inline bool operator _op_ (const U* o) const {                  \
    return m_ptr _op_ o;                                        \
}