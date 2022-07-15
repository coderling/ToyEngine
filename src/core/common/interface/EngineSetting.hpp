#pragma once
#include <cstdint>
#include <string>

namespace Toy::Engine
{
struct EngineD3D12Setting final
{
    static constexpr const uint32_t MAX_NUM_SAMPLER = 2048;

    struct GPUHeapSize
    {
        uint32_t cbv_srv_uav;
        uint32_t sampler;
    };

    struct GPUDynamicChunkSize
    {
        uint32_t cbv_srv_uav;
        uint32_t sampler;
    };

    struct CPUHeapSize
    {
        uint32_t cbv_srv_uav;
        uint32_t sampler;
        uint32_t rtv;
        uint32_t dsv;
    };

    GPUHeapSize GPU_static_mutable{8912, 1024};
    GPUHeapSize GPU_dynamic{8912, 1024};
    GPUDynamicChunkSize GPU_dynamic_chunk_size{256, 32};

    CPUHeapSize CPU_heap_size{8912, 2048, 1024, 1024};
};

struct EngineSetting final
{
    bool use_wrap_device = false;

    int32_t frame_count = 3;

    bool hdr = false;

    std::string data_path;

    EngineD3D12Setting d3d12;
};

}  // namespace Toy::Engine