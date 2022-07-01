#pragma once
#include "DescriptorHeap.hpp"

namespace Toy::Graphics
{
class CommandContext
{
    CPUDescriptorHeap cpu_descriptorheap[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];

   public:
};
}  // namespace Toy::Graphics