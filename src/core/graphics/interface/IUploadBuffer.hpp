#pragma once
#include <memory>
#include <string>
#include "IGPUResource.hpp"
#include "pch.hpp"


namespace Toy::Graphics
{
class TOY_LIB_API IUploadBuffer : public IGPUResource
{
   public:
    static std::unique_ptr<IUploadBuffer> Create(const std::string& name, size_t size);
    virtual void* Map(void) = 0;

    virtual void UnMap(size_t begin = 0, size_t = -1) = 0;

    virtual size_t GetBufferSize() = 0;

   protected:
    virtual void Init(const std::string& name, size_t size) = 0;
};
}  // namespace Toy::Graphics