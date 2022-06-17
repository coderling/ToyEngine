#pragma once

#include <cstdint>
#include <memory>
#include "GraphicsDef.hpp"
#include "IObject.hpp"
#include "pch.hpp"


namespace Toy::Graphics
{
class TOY_LIB_API IGraphicsCommandList : public Toy::Engine::IObject, public Toy::Engine::NoCopy
{
   public:
    static std::unique_ptr<IGraphicsCommandList> Create(const uint32_t& node_mask, const COMMAND_LIST_TYPE& t);
    virtual IDeviceCommandList* GetCmdList() const noexcept = 0;
    virtual void Reset() = 0;
    virtual void Close() = 0;
};
}  // namespace Toy::Graphics