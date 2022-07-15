#pragma once
namespace Toy
{
struct IAllocator
{
    virtual ~IAllocator() {}
    virtual void* Allocate(size_t size, const char* dbg_descirption, const char* dbg_filename, const int& dbg_line) = 0;
    virtual void Free(void* ptr) = 0;
};
}  // namespace Toy