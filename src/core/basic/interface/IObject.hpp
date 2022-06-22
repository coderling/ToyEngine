#pragma once
#include "CommonDefines.hpp"
#include "InterfaceUUID.hpp"

namespace Toy
{
class IReferenceCounter;

class IObject
{
   public:
    virtual TOY_RESULT ENGINE_FUNCTION_CALL_CONVENTION QueryInterface(const IUUID& iid, IObject** pp_interface) = 0;
    virtual ~IObject() {}

   protected:
    template <typename OtherInterface>
    class RefWeakPtr;
    template <typename OtherInterface>
    class RefCountPtr;
    virtual uint64_t ENGINE_FUNCTION_CALL_CONVENTION AddReference() = 0;
    virtual uint64_t ENGINE_FUNCTION_CALL_CONVENTION Release() = 0;
    virtual IReferenceCounter* GetReferenceCounter() = 0;
};
}  // namespace Toy