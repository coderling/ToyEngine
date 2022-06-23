#pragma once
#include "CommonDefines.hpp"
#include "InterfaceUUID.hpp"

namespace Toy::Engine
{
template <typename OtherInterface>
class RefCountWeakPtr;
template <typename OtherInterface>
class RefCountPtr;
}  // namespace Toy::Engine

namespace Toy
{
class IReferenceCounter;

class IObject
{
   public:
    virtual TOY_RESULT ENGINE_FUNCTION_CALL_CONVENTION QueryInterface(const IUUID& iid, IObject** pp_interface) = 0;
    void Destroy() { OnDestroy(); }
    virtual ~IObject() noexcept {}

   protected:
    template <typename OtherInterface>
    friend class Toy::Engine::RefCountWeakPtr;
    template <typename OtherInterface>
    friend class Toy::Engine::RefCountPtr;
    virtual long AddReference() = 0;
    virtual long Release() = 0;
    virtual IReferenceCounter* GetReferenceCounter() = 0;
    virtual void OnDestroy() = 0;
};
}  // namespace Toy