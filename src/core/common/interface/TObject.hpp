#pragma once
#include "ReferenceCounterObject.hpp"

namespace Toy::Engine
{
template <typename Interface>
requires std::derived_from<Interface, IObject>
class TObject : public ReferenceCounterObject<Interface>
{
   public:
    TObject(IReferenceCounter* _p_refcounter) noexcept : ReferenceCounterObject<Interface>(_p_refcounter) {}

    TOY_RESULT ENGINE_FUNCTION_CALL_CONVENTION QueryInterface(const IUUID& iid, IObject** pp_interface) override
    {
        if (pp_interface == nullptr)
            {
                return TOY_RESULT::TR_ERROR;
            }

        if (iid == UUID_UNKNOWN)
            {
                *pp_interface = this;
                (*pp_interface)->AddReference();
                return TOY_RESULT::TR_OK;
            }
        return TOY_RESULT::TR_ERROR;
    }
};

#define IMPLEMENT_QUERYINTERFACE_LOGIC(IID_VALUE, BASE_CLASS_TYPE)                                                                         \
    {                                                                                                                                      \
        if (pp_interface == nullptr)                                                                                                       \
            {                                                                                                                              \
                return TOY_RESULT::TR_ERROR;                                                                                               \
            }                                                                                                                              \
                                                                                                                                           \
        if (iid == IID_VALUE)                                                                                                              \
            {                                                                                                                              \
                *pp_interface = this;                                                                                                      \
                (*pp_interface)->AddReference();                                                                                           \
                return TOY_RESULT::TR_OK;                                                                                                  \
            }                                                                                                                              \
        else                                                                                                                               \
            {                                                                                                                              \
                return BASECLASS_TYPE::QueryInterface(IID_VALUE, pp_interface);                                                            \
            }                                                                                                                              \
        return TOY_RESULT::TR_ERROR;                                                                                                       \
    }

#define IMPLEMENT_QUERYINTERFACE(CLASS_TYPE, BASE_CLASS_TYPE)                                                                              \
    TOY_RESULT ENGINE_FUNCTION_CALL_CONVENTION CLASS_TYPE::QueryInterface(const IUUID& iid, IObject** pp_interface)                        \
        IMPLEMENT_QUERYINTERFACE_LOGIC(CLASS_TYPE::CLS_UUID, BASE_CLASS_TYPE)

#define IMPLEMENT_QUERYINTERFACE_LOCALLY(CLASS_TYPE, BASE_CLASS_TYPE)                                                                      \
    TOY_RESULT ENGINE_FUNCTION_CALL_CONVENTION QueryInterface(const IUUID& iid, IObject** pp_interface) override                           \
    IMPLEMENT_QUERYINTERFACE_LOGIC(CLASS_TYPE::CLS_UUID, BASE_CLASS_TYPE)

}  // namespace Toy::Engine