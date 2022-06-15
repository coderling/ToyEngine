#include "UploadBuffer_D3D12.hpp"
#include <IGraphics.hpp>
#include <algorithm>
#include "EngineUtility.hpp"
#include "GlobalEnvironment.hpp"
#include "IApp.hpp"
#include "Utility.hpp"
#include "d3dx12.h"


using namespace Toy::Graphics;

std::unique_ptr<IUploadBuffer> IUploadBuffer::Create(const std::string& name, size_t size)
{
    auto buffer = std::make_unique<UploadBuffer>();
    buffer->Init(name, size);

    return buffer;
}

void UploadBuffer::Init(const std::string& name, size_t size)
{
    Release();

    buffer_size = size;

    D3D12_HEAP_PROPERTIES heap_props;
    heap_props.Type = D3D12_HEAP_TYPE_UPLOAD;  // upload buffer, avoid reading back from it
    heap_props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heap_props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heap_props.CreationNodeMask = 1;
    heap_props.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC resource_desc = {};
    resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resource_desc.Width = buffer_size;
    resource_desc.Height = 1;
    resource_desc.DepthOrArraySize = 1;  // limit one dimension
    resource_desc.MipLevels = 1;
    resource_desc.Format = DXGI_FORMAT_UNKNOWN;
    resource_desc.SampleDesc.Count = 1;
    resource_desc.SampleDesc.Quality = 0;
    resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;

    auto device = Toy::Engine::IApp::env->GetGraphics()->GetDevice();
    ASSERT_SUCCEEDED(device->CreateCommittedResource(&heap_props, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                                     nullptr, MY_IID_PPV_ARGS(&resource.p_resource)));

    resource.gpu_virtual_address = resource.p_resource->GetGPUVirtualAddress();

#ifdef RELEASE
#else
    resource.p_resource->SetName(s2ws(name).c_str());
#endif
}

void* UploadBuffer::Map()
{
    void* memory = nullptr;
    const auto& range = CD3DX12_RANGE(0, buffer_size);
    resource.p_resource->Map(0, &range, &memory);

    return memory;
}

void UploadBuffer::UnMap(size_t begin, size_t end)
{
    const auto& range = CD3DX12_RANGE(begin, std::min(end, buffer_size));
    resource.p_resource->Unmap(0, &range);
}

IDeviceResource* UploadBuffer::GetResource() { return resource.GetResource(); }

const IDeviceResource* UploadBuffer::GetResource() const { return resource.GetResource(); }

IDeviceResource** UploadBuffer::GetAddressOf() { return resource.GetAddressOf(); }

GPU_VIRTUAL_ADDRESS UploadBuffer::GetGpuVirtualAddress() const { return resource.GetGpuVirtualAddress(); }

void UploadBuffer::OnDestroy() { resource.Destroy(); }
void UploadBuffer::Release() { resource.Release(); }