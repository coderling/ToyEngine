#pragma once
#include <cstdio>
#include "IObject.hpp"

namespace Toy::Engine
{
struct IDataBlob : public IObject
{
    static constexpr const IUUID CLS_UUID = {/* 426e7699-1d32-469e-872f-5d5068c34161 */
                                             0x426e7699,
                                             0x1d32,
                                             0x469e,
                                             {0x87, 0x2f, 0x5d, 0x50, 0x68, 0xc3, 0x41, 0x61}};

    virtual std::size_t GetDataSize() const = 0;
    virtual void* GetDataPointer() = 0;
    virtual const void* GetDataPointer() const = 0;
    virtual void Resize(const std::size_t& size) = 0;
};
}  // namespace Toy::Engine