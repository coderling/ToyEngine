#pragma once

#include <IPipelineFragmentHandler.hpp>
#include <iostream>
#include "d3dx12.h"
#include <wrl.h>

using namespace Microsoft::WRL;

class RenderLogic : public Toy::Graphics::IPipelineFragmentHandler
{
public:
	void Load() override
	{
		std::cout << "RenderLogic::Load" << std::endl;
	}

	void Render() override
	{
		std::cout << "RenderLogic::OnRender()" << std::endl;
	}
	
	void Unload() override
	{
		std::cout << "RenderLogic::Unload()" << std::endl;
	}

protected:
	void OnDestroy() override
	{
		std::cout << "RenderLogic::Destroy()" << std::endl;
	}

private:
	ComPtr<ID3D12RootSignature> root_signature;
	ComPtr<ID3D12DescriptorHeap> rtv_heap;
	ComPtr<ID3D12PipelineState> pipeline_state;

	ComPtr<ID3D12Resource> vertex_buffer;
	D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
};
