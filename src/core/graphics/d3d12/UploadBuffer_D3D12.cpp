#include <algorithm>
#include "d3dx12.h"
#include "UploadBuffer_D3D12.hpp"
#include "Utility.hpp"
#include "../../interface/GlobalEnvironment.hpp"


using namespace Toy::Graphics;

void UploadBuffer::Create(const std::wstring& name, size_t size)
{
	Destroy();

	buffer_size = size;
	
	D3D12_HEAP_PROPERTIES heap_props;
	heap_props.Type = D3D12_HEAP_TYPE_UPLOAD; // upload buffer, avoid reading back from it
	heap_props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap_props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap_props.CreationNodeMask = 1;
	heap_props.VisibleNodeMask = 1;

	D3D12_RESOURCE_DESC resource_desc = {};
	resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER; 
	resource_desc.Width = buffer_size;
	resource_desc.Height = 1;
	resource_desc.DepthOrArraySize = 1; //limit one dimension
	resource_desc.Format = DXGI_FORMAT_UNKNOWN;
	resource_desc.SampleDesc.Count = 1;
	resource_desc.SampleDesc.Quality = 0;
	resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	ASSERT_SUCCEEDED(device->CreateCommittedResource(&heap_props, D3D12_HEAP_FLAG_NONE,
		&resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, MY_IID_PPV_ARGS(&p_resource) ));

	gpu_virtual_address = p_resource->GetGPUVirtualAddress();

#ifdef RELEASE
#else
	p_resource->SetName(name.c_str());
#endif
}

void* UploadBuffer::Map()
{
	void* memory = nullptr;
	const auto& range = CD3DX12_RANGE(0, buffer_size);
	p_resource->Map(0, &range, &memory);

	return memory;
}

void UploadBuffer::UnMap(size_t begin, size_t end)
{
	const auto& range = CD3DX12_RANGE(begin, (std::min)(end, buffer_size));
	p_resource->Unmap(0, &range);
}