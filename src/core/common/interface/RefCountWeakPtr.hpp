#pragma once

#include "DebugUtility.hpp"
#include "RefCountPtr.hpp"
#include "ReferenceCounter.hpp"

namespace Toy::Engine
{
template <typename Interface>
requires std::derived_from<Interface, IObject>
class RefCountWeakPtr final
{
    Interface* p_object;
    ReferenceCounter* p_refcounter;

   public:
    explicit RefCountWeakPtr(Interface* _p_object = nullptr) noexcept : p_object(_p_object), p_refcounter(nullptr)
    {
        if (p_object != nullptr)
            {
                p_refcounter = StaticCheckPointerCast<ReferenceCounter, IReferenceCounter>(p_object->GetReferenceCounter());
            }
    }

    ~ReferenceCounter() noexcept { Release(); }

    // 赋值构造函数
    RefCountWeakPtr(const RefCountWeakPtr& ref_ptr) noexcept : p_object(ref_ptr.p_object), p_refcounter(ref_ptr.p_refcounter)
    {
        if (p_refcounter != nullptr)
            {
                p_refcounter->AddWeakRef();
            }
    }

    // 移动构造函数
    RefCountWeakPtr(RefCountWeakPtr&& ref_ptr) noexcept
        : p_object(std::move(ref_ptr.p_object)), p_refcounter(std::move(ref_ptr.p_refcounter))
    {
        ref_ptr.p_object = nullptr;
        ref_ptr.p_refcounter = nullptr;
    }

    // 由RefCountPtr的类型转换，显式
    explicit RefCountWeakPtr(RefCountPtr<Interface>& ref_ptr) noexcept : p_object(ref_ptr.RawPtr()), p_refcounter(nullptr)
    {
        if (p_object != nullptr)
            {
                p_refcounter = Debug::StaticCheckPointerCast<ReferenceCounter, IReferenceCounter>(p_object->GetReferenceCounter());
            }
        if (p_refcounter != nullptr)
            {
                p_refcounter->AddWeakRef();
            }
    }

    // 赋值
    RefCountWeakPtr& operator=(const RefCountWeakPtr& ref_ptr) noexcept
    {
        if (*this == ref_ptr)
            {
                return *this;
            }
        Release();
        p_object = ref_ptr.p_object;
        p_refcounter = ref_ptr.p_refcounter;
        if (p_refcounter != nullptr)
            {
                p_refcounter->AddWeakRef();
            }

        return *this;
    }

    // 赋值，原生指针到weakptr
    RefCountWeakPtr& operator=(Interface* _p_object) noexcept
    {
        if (p_object == _p_object)
            {
                return *this;
            }

        p_object = _p_object;
        if (p_object != nullptr)
            {
                p_refcounter = Debug::StaticCheckPointerCast<ReferenceCounter, IReferenceCounter>(p_object->GetReferenceCounter());
            }
        if (p_refcounter != nullptr)
            {
                p_refcounter->AddWeakRef();
            }
    }

    // 移动赋值函数 move construct
    RefCountWeakPtr& operator=(RefCountWeakPtr&& ref_ptr) noexcept
    {
        if (*this == ref_ptr)
            {
                return *this;
            }

        Release();
        p_object = std::move(ref_ptr.p_object);
        p_refcounter = std::move(ref_ptr.p_refcounter);

        ref_ptr.p_object = nullptr;
        ref_ptr.p_refcounter = nullptr;

        return *this;
    }

    // 移动赋值函数，由RefCountPtr到weakptr
    RefCountWeakPtr& operator=(RefCountPtr<Interface> ref_ptr) noexcept
    {
        Release();
        p_object = ref_ptr.RawPtr();
        if (p_object != nullptr)
            {
                p_refcounter = Debug::StaticCheckPointerCast<ReferenceCounter, IReferenceCounter>(p_object->GetReferenceCounter());
            }

        if (p_refcounter != nullptr)
            {
                p_refcounter->AddWeakRef();
            }
    }

    void Release() noexcept
    {
        if (p_refcounter != nullptr)
            {
                p_refcounter->ReleaseWeakRef();
            }
        p_refcounter = nullptr;
        p_object = nullptr;
    }

    bool IsValid() const noexcept { return p_object != nullptr && p_refcounter != nullptr && p_refcounter->GetNumOfStrongRef() > 0; }

    RefCountPtr<Interface> Lock()
    {
        RefCountPtr<Interface> strong_ptr;
        if (p_refcounter != nullptr)
            {
                RefCountPtr<Interface> p_owner;
                p_refcounter->GetObject(&p_owner);
                if (p_owner != nullptr)
                    {
                        strong_ptr = p_object;
                    }
                else
                    {
                        Release();
                    }
            }

        return strong_ptr;
    }

    bool operator==(const RefCountWeakPtr& rhs) const noexcept { return p_refcounter == rhs.p_refcounter; }
    bool operator!=(const RefCountWeakPtr& rhs) const noexcept { return p_refcounter != rhs.p_refcounter; }
};

}  // namespace Toy::Engine