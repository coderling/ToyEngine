#pragma once

#include "TObject.hpp"

namespace Toy::Graphics
{

class IDeviceObject : public IObject
{
    INTERFACEUUID(IDeviceObject) = {/* 426e7699-1d32-469e-872f-5d5068c34161 */
                                    0x426e7699,
                                    0x1d32,
                                    0x469e,
                                    {0x87, 0x2f, 0x5d, 0x50, 0x68, 0xc3, 0x41, 0x61}};
};

template <typename DeviceObjectInterface>
requires std::derived_from<DeviceObjectInterface, IDeviceObject>
class DeviceObject : public Engine::TObject<DeviceObjectInterface>
{
    using TBase = Engine::TObject<DeviceObjectInterface>;

   public:
    DeviceObject(IReferenceCounter* p_refcounter)
        : TBase(p_refcounter)
    {
    }
};
}  // namespace Toy::Graphics