#pragma once

#include <wrl.h>

#include "IGraphicsCommandList.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
class GraphicsCommandList : public IGraphicsCommandList
{
   public:
    GraphicsCommandList();
    GraphicsCommandList(const uint32_t& node_mask, const COMMAND_LIST_TYPE& t);
    ID3D12GraphicsCommandList* GetCmdList() const noexcept override { return command_list.Get(); }
    void OnDestroy() override;
    void Reset() override;
    void Close() override;

   private:
    void Create(const uint32_t& node_mask, const COMMAND_LIST_TYPE& t);
    ComPtr<ID3D12GraphicsCommandList> command_list;
    ComPtr<ID3D12CommandAllocator> command_allocator;
};
}  // namespace Toy::Graphics