#pragma once

#include <limits>
#include <memory>
#include "IAllocator.hpp"


namespace Toy::Engine
{
template <typename T>
typename std::enable_if<std::is_destructible<T>::value, void>::type Destruct(T* ptr)
{
    ptr->~T();
}

template <typename T>
typename std::enable_if<!std::is_destructible<T>::value, void>::type Destruct(T* ptr)
{
}

template <typename T, typename AllocatorType>
struct STDAllocator
{
   public:
    using value_type = T;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    STDAllocator(AllocatorType& allocator, const char* description, const char* filename, const int& line) noexcept
        : allocator(allocator)
#ifdef ENGINE_DEVELOPMENT
          ,
          description(description),
          filename(filename),
          linenumber(line)
#endif
    {
    }

    template <typename U>
    STDAllocator(const STDAllocator<U, AllocatorType>& other) noexcept
        : allocator(other.allocator)
#ifdef ENGINE_DEVELOPMENT
          ,
          description(other.description),
          filename(other.filename),
          linenumber(other.linenumber)
#endif
    {
    }

    template <typename U>
    STDAllocator(STDAllocator<U, AllocatorType>&& other) noexcept
        : allocator(other.allocator)
#ifdef ENGINE_DEVELOPMENT
          ,
          description(other.description),
          filename(other.filename),
          linenumber(other.linenumber)
#endif
    {
    }

    template <typename U>
    struct rebind
    {
        typedef STDAllocator<U, AllocatorType> other;
    };

    T* allocate(std::size_t count)
    {
#ifndef ENGINE_DEVELOPMENT
        static constexpr const char* description = "<Unavailable in release build>";
        static constexpr const char* filename = "<Unavailable in release build>";
        static constexpr int linenumber = -1;
#endif
        return reinterpret_cast<T*>(allocator.Allocate(count * sizeof(T), description, filename, linenumber));
    }

    pointer address(reference r) { return &r; }
    const_pointer address(const_reference r) { return &r; }

    void deallocate(T* p, std::size_t count) { allocator.Free(p); }

    inline size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(T); }

#ifdef ENGINE_DEVELOPMENT
    const char* const description;
    const char* const filename;
    const int linenumber;
#endif

    AllocatorType& allocator;
};

#define STD_ALLOCATOR(Type, AllocatorType, Allocator, Description)                                                                         \
    STDAllocator<Type, AllocatorType>(Allocator, Description, __FILE__, __LINE__)

template <class T, class U, class A>
bool operator==(const STDAllocator<T, A>& left, const STDAllocator<U, A>& right)
{
    return &left.allocator == &right.allocator;
}

template <class T, class U, class A>
bool operator!=(const STDAllocator<T, A>& left, const STDAllocator<U, A>& right)
{
    return !(left == right);
}

template <class T>
using STDAllocatorRawMem = STDAllocator<T, IAllocator>;
#define STD_ALLOCATOR_RAWMEM(Type, Allocator, Description) STDAllocatorRawMem<Type>(Allocator, Description, __FILE__, __LINE__)

template <class T, typename AllocatorType>
struct STDDeleter
{
    STDDeleter() noexcept {}
    STDDeleter(AllocatorType& allocator) noexcept : allocator(allocator) {}
    STDDeleter& operator=(const STDDeleter&) = default;
    STDDeleter(STDDeleter&& rhs) noexcept : allocator(rhs.allocator) { rhs.allocator = nullptr; }

    STDDeleter& operator=(STDDeleter&& rhs) noexcept
    {
        allocator = rhs.allocator;
        rhs.allocator = nullptr;
        return *this;
    }

    void operator()(T* ptr) noexcept
    {
        Destruct(ptr);
        allocator->Free(ptr);
    }

   private:
    AllocatorType* allocator = nullptr;
};

template <class T>
using STDDeleterRawMen = STDDeleter<T, IAllocator>;
}  // namespace Toy::Engine