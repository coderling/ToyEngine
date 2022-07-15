#pragma once
#include <wrl.h>
#include <unordered_map>
#include "D3D12TypeTraits.hpp"
#include "IPipelineStateD3D12.hpp"
#include "PipelineStateBase.hpp"
#include "d3dx12.h"


using namespace Microsoft::WRL;
namespace Toy::Graphics
{
class PipelineStateD3D12 : public PipelineStateBase<D3D12TypeTraits>
{
   public:
};
}  // namespace Toy::Graphics