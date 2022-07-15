#pragma once
#include "IBuffer.hpp"
#include "IObject.hpp"
#include "IPipelineState.hpp"

namespace Toy::Graphics
{

struct DrawArgs final
{
    uint32_t num_verteies;
    uint32_t num_instance;
    uint32_t start_location;
    uint32_t start_instance_location;
};

class IDeviceContext : public IObject
{
   public:
    INTERFACEUUID(IRenderDevice) = {/* 93fad31a-324e-4248-9385-6b61224996ae */
                                    0x93fad31a,
                                    0x324e,
                                    0x4248,
                                    {0x93, 0x85, 0x6b, 0x61, 0x22, 0x49, 0x96, 0xae}};

    virtual void SetPipelineState(IPipelineState* pipelinestate) = 0;
    virtual void SetVertexBuffers(const uint32_t& start_slot, IBuffer** pp_buffers, const std::size_t& num) = 0;
    virtual void SetIndexBuffers(const std::size_t& byte_offset, IBuffer* p_index_buffer) = 0;
    virtual void Draw(const DrawArgs&);
};
}  // namespace Toy::Graphics