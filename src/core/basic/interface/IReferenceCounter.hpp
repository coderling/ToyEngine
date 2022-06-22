#pragma once

namespace Toy
{
class IReferenceCounter
{
   public:
    virtual long AddStrongRef() = 0;
    virtual long ReleaseStrongRef() = 0;
    virtual long GetNumOfStrongRef() const = 0;

    virtual long AddWeakRef() = 0;
    virtual long ReleaseWeakRef() = 0;
    virtual long GetNumOfWeakRef() const = 0;

    virtual void GetObject(class IObject** pp_object) = 0;
    virtual ~IReferenceCounter() = 0;
};
}  // namespace Toy