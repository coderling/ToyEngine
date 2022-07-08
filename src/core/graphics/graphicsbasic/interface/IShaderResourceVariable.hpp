#pragma once
#include <DeviceObject.hpp>
#include <string_view>
#include "IObject.hpp"


namespace Toy::Graphics
{
class IShaderResourceVariable : public IObject
{
    INTERFACEUUID(IShaderResourceVariable) = {/* 2ad8b601-a27c-497a-a642-ba72bd9a0673 */
                                              0x2ad8b601,
                                              0xa27c,
                                              0x497a,
                                              {0xa6, 0x42, 0xba, 0x72, 0xbd, 0x9a, 0x06, 0x73}};

   public:
    virtual void Set(const std::string_view& str, IDeviceObject* object) = 0;
};
}  // namespace Toy::Graphics