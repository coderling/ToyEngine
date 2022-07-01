#include "IReferenceCounter.hpp"
#include "TObject.hpp"

namespace Toy::Graphics
{
template <typename DeviceObjectInterface>
class DeviceObject : public Engine::TObject<DeviceObjectInterface>
{
    using TBase = Engine::TObject<DeviceObjectInterface>;

   public:
    DeviceObject(IReferenceCounter* p_refcounter) : TBase(p_refcounter) {}
};
}  // namespace Toy::Graphics