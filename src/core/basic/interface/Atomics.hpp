#pragma once
#if PLATFORM_WINDOWS
#include <Windows.h>
typedef volatile long AtomicInt32;
typedef volatile long long AtomicInt64;
#else
#include <atomic>

typedef std::atomic<long> AtomicInt32;
typedef std::atomic<long long> AtomicInt64;
#endif

namespace Toy
{
struct Atomics
{
    template <typename AtomicType, typename RType>
    static inline RType Increment(AtomicType& val)
    {
    }
    template <typename AtomicType, typename RType>
    static inline RType Decrement(AtomicType& val)
    {
#if PLATFORM_WINDOWS
        return Win_InterlockedDecrement<AtomicType, RType>(&val);
#else
        return --val;
#endif
    }
    static inline long Increment(AtomicInt32& val)
    {
#if PLATFORM_WINDOWS
        return InterlockedIncrement(&val);
#else
        return ++val;
#endif
    }

    static inline long long Increment(AtomicInt64& val)
    {
#if PLATFORM_WINDOWS
        return InterlockedIncrement64(&val);
#else
        return ++val;
#endif
    }

    static inline long Decrement(AtomicInt32& val)
    {
#if PLATFORM_WINDOWS
        return InterlockedDecrement(&val);
#else
        return --val;
#endif
    }

    static inline long long Decrement(AtomicInt64& val)
    {
#if PLATFORM_WINDOWS
        return InterlockedDecrement64(&val);
#else
        return --val;
#endif
    }

    static inline long CompareExchange(AtomicInt32& dest, long expected, long desired)
    {
#if PLATFORM_WINDOWS
        return InterlockedCompareExchange(&dest, desired, expected);
#else
        dest.compare_exchange_strong(expected, desired);
        return desired;
#endif
    }

    static inline long CompareExchange(AtomicInt64& dest, long long expected, long long desired)
    {
#if PLATFORM_WINDOWS
        return InterlockedCompareExchange64(&dest, desired, expected);
#else
        dest.compare_exchange_strong(expected, desired);
        return desired;
#endif
    }

    static inline long Add(AtomicInt32& dest, const long& val)
    {
#if PLATFORM_WINDOWS
        return InterlockedAdd(&dest, val);
#else
        return dest.fetch_add(val);
#endif
    }

    static inline long long Add(AtomicInt64& dest, const long long& val)
    {
#if PLATFORM_WINDOWS
        return InterlockedAdd64(&dest, val);
#else
        return dest.fetch_add(val);
#endif
    }
};
}  // namespace Toy