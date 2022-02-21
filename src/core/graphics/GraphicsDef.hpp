#pragma once

// d3d12
#include <d3d12.h>
#include <dxgi1_6.h>

typedef ID3D12Resource IDeviceResource;
typedef D3D12_GPU_VIRTUAL_ADDRESS GPU_VIRTUAL_ADDRESS;
#define GPU_VIRTUAL_ADDRESS_NULL ((GPU_VIRTUAL_ADDRESS)0)
#define GPU_VIRTUAL_ADDRESS_UNKNOWN ((GPU_VIRTUAL_ADDRESS)-1)
#define MY_IID_PPV_ARGS IID_PPV_ARGS

typedef ID3D12Device IDevice;
typedef ID3D12CommandQueue IDeviceCommandQueue;
typedef ID3D12CommandAllocator IDeviceCommandAllocator;
typedef ID3D12GraphicsCommandList IDeviceCommandList;

// command queue args
typedef D3D12_COMMAND_QUEUE_DESC  COMMAND_QUEUE_DESC;

// common
