#pragma once

#include "CommonDefines.hpp"
#include "IAllocator.hpp"

namespace Toy::Engine
{
class DefaultMemoryAllocator final : public IAllocator
{
   public:
    DefaultMemoryAllocator();
    NODISCARD void* Allocate(size_t size, const char* dbg_descirption, const char* dbg_filename, const int dbg_line) override;
    void Free(void* ptr) override;
    static DefaultMemoryAllocator& GetGobalAllocator();

    // no copy
    NOCOPY_INPLACE(DefaultMemoryAllocator);
};
}  // namespace Toy::Engine