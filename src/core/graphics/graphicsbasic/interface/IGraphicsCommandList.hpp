#pragma once

#include <cstdint>
#include <memory>
#include "GraphicsDef.hpp"
#include "IObject.hpp"

namespace Toy::Graphics
{
class IGraphicsCommandList : public IObject
{
   public:
    static std::unique_ptr<IGraphicsCommandList> Create(const uint32_t& node_mask, const COMMAND_LIST_TYPE& t);
    virtual IDeviceCommandList* GetCmdList() const noexcept = 0;
    virtual void Reset() = 0;
    virtual void Close() = 0;
};
}  // namespace Toy::Graphics