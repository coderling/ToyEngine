#pragma once

#include <wrl.h>

#include "IGraphicsCommandList.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
	class GraphicsCommandList : public IGraphicsCommandList
	{
	public:
		ID3D12GraphicsCommandList* GetCmdList()const noexcept { return command_list.Get(); }
	private:
		ComPtr<ID3D12GraphicsCommandList > command_list;
	};
}