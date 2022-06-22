#pragma once
#include <cstdio>

namespace Toy::Engine
{
struct IDataBlob
{
    virtual std::size_t GetDataSize() = 0;
    virtual void* GetDataPointer() = 0;
    virtual const void* GetDataPointer() const = 0;
};
}  // namespace Toy::Engine