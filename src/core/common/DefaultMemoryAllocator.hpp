#pragma once

#include <IAllocator.hpp>
#include <IObject.hpp>

namespace Toy::Engine
{
class TOY_LIB_API DefaultMemoryAllocator final : public IAllocator, NoCopy
{
   public:
    void* Allocate(size_t size, const char* dbg_descirption, const char* dbg_filename, const int dbg_line) override;
    void Free(void* ptr) override;
    static DefaultMemoryAllocator& GetGobalAllocator();
};
}  // namespace Toy::Engine