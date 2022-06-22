#pragma once
#include <functional>

namespace Toy::Engine
{
// boost hash_combine
template <typename T>
inline void HashCombine(std::size_t& hash, const T& v)
{
    return std::hash<T>(v) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
}

template <typename Iter>
inline std::size_t HansRange(Iter begin, Iter end)
{
    std::size_t hash = 0;
    for (; begin != end; ++begin)
        {
            HashCombine(hash, *begin);
        }
    return hash;
}

}  // namespace Toy::Engine