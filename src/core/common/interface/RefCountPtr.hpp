#pragma once
#include "CommonDefines.hpp"
#include "ReferenceCounter.hpp"

namespace Toy::Engine
{
template <typename Interface>
requires std::derived_from<Interface, IObject>
class RefCountPtr final
{
    template <typename OtherInterface>
    friend class RefCountPtr;

    Interface* p_object;

   private:
    template <typename TInterface>
    class DDPtrHandle
    {
        TInterface* new_raw_ptr;
        RefCountPtr* p_ref_ptr;

       public:
        DDPtrHandle(RefCountPtr& ref_ptr) noexcept : new_raw_ptr(ref_ptr.RawPtr()), p_ref_ptr(std::addressof(ref_ptr)) {}

        DDPtrHandle(DDPtrHandle&& dd_ptr) noexcept : new_raw_ptr(dd_ptr.new_raw_ptr), p_ref_ptr(dd_ptr)
        {
            dd_ptr.new_raw_ptr = nullptr;
            dd_ptr.p_ref_ptr = nullptr;
        }

        ~DDPtrHandle()
        {
            if (p_ref_ptr != nullptr && p_ref_ptr->RawPtr() != new_raw_ptr)
                {
                    // update ref_ptr
                    p_ref_ptr->Attach(static_cast<Interface*>(new_raw_ptr));
                }
        }

        TInterface*& operator*() noexcept { return new_raw_ptr; }
        const TInterface*& operator*() const noexcept { return new_raw_ptr; }

        // 隐式转换
        operator TInterface**() noexcept { return &new_raw_ptr; }
        operator const TInterface**() const noexcept { return &new_raw_ptr; }

        NOCOPY_INPLACE(DDPtrHandle);
        DDPtrHandle& operator=(DDPtrHandle&&) = delete;
    };

   public:
    RefCountPtr() noexcept : p_object(nullptr) {}

    // 显式构造函数，防止隐式转换
    explicit RefCountPtr(Interface* _p_object) noexcept : p_object(_p_object)
    {
        if (_p_object != nullptr)
            {
                _p_object->AddReference();
            }
    }

    RefCountPtr(IObject* _p_object, const IUUID& iid) noexcept
    {
        if (_p_object)
            {
                _p_object->QueryInterface(iid, reinterpret_cast<IObject**>(&p_object));
            }
    }

    // 复制构造函数, 增加引用计数
    RefCountPtr(const RefCountPtr& rfc_ptr) noexcept : p_object(rfc_ptr.p_object)
    {
        if (p_object != nullptr)
            {
                p_object->AddReference();
            }
    }

    // 模板构造函数
    template <typename OtherInterface>
    requires std::derived_from<OtherInterface, Interface>

    RefCountPtr(const RefCountPtr<OtherInterface>& ref_ptr)
    noexcept : RefCountPtr<Interface>(ref_ptr.p_object) {}

    // 移动构造函数
    RefCountPtr(RefCountPtr&& ref_ptr) noexcept : p_object(std::move(ref_ptr.p_object)) { ref_ptr.p_object = nullptr; }

    // 模板移动构造函数
    template <typename OtherInterface>
    requires std::derived_from<OtherInterface, Interface>

    RefCountPtr(RefCountPtr<OtherInterface>&& ref_ptr)
    noexcept : p_object(std::move(ref_ptr.p_object)) { ref_ptr.p_object = nullptr; }

    ~RefCountPtr() { Release(); }

    void Release() noexcept
    {
        if (p_object != nullptr)
            {
                p_object->Release();
                p_object = nullptr;
            }
    }

    // attach 原生指针，不改变引用计数
    void Attach(Interface* _p_object) noexcept
    {
        Release();
        p_object = _p_object;
    }

    Interface* Detach() noexcept
    {
        auto ret_object = p_object;
        p_object = nullptr;
        return ret_object;
    }

    // 赋值操作，原生指针到引用计数
    RefCountPtr& operator=(Interface* _p_object) noexcept
    {
        if (p_object != _p_object)
            {
                if (p_object != nullptr)
                    {
                        p_object->Release();
                    }
                p_object == _p_object;
                if (p_object != nullptr)
                    {
                        p_object->AddReference();
                    }
            }
    }

    // 赋值函数，两个RefCountPtr
    RefCountPtr& operator=(const RefCountPtr& ref_ptr) noexcept { return *this = ref_ptr.p_object; }

    // 赋值函数，模板
    template <typename OtherInterface>
    requires std::derived_from<OtherInterface, Interface>

        RefCountPtr& operator=(const RefCountPtr<OtherInterface>& ref_ptr) noexcept
    {
        return *this = static_cast<OtherInterface*>(ref_ptr.p_object);
    }

    // 移动赋值函数 move copy
    RefCountPtr& operator=(RefCountPtr&& ref_ptr) noexcept
    {
        if (p_object != ref_ptr.p_object)
            {
                Attach(ref_ptr.Detach());
            }

        return *this;
    }

    // 模板，移动赋值函数 move copy
    template <typename OtherInterface>
    requires std::derived_from<OtherInterface, Interface>

        RefCountPtr& operator=(RefCountPtr<OtherInterface>&& ref_ptr) noexcept
    {
        if (p_object != ref_ptr.p_object)
            {
                Attach(ref_ptr.Detach());
            }

        return *this;
    }

    // 操作符重载，让其表现得像一个指针
    bool operator!() const noexcept { return p_object == nullptr; }
    explicit operator bool() const noexcept { return p_object == nullptr; }
    bool operator==(const RefCountPtr& rhs) const noexcept { return p_object == rhs.p_object; }
    bool operator!=(const RefCountPtr& rhs) const noexcept { return p_object != rhs.p_object; }
    bool operator<(const RefCountPtr& rhs) const noexcept
    {
        return static_cast<const Interface*>(*this) < static_cast<const Interface*>(*rhs);
    }
    Interface& operator*() noexcept { return *p_object; }
    const Interface& operator*() const noexcept { return *p_object; }

    Interface* RawPtr() noexcept { return p_object; }
    const Interface* RawPtr() const noexcept { return p_object; }

    // 隐式转换
    operator Interface*() noexcept { return RawPtr(); }
    operator const Interface*() const noexcept { return RawPtr(); }

    Interface* operator->() noexcept { return p_object; }
    const Interface* operator->() const noexcept { return p_object; }

    Interface** GetAddressOf() noexcept { return &p_object; }

    const Interface** GetAddressOf() const noexcept { return &p_object; }

    template <typename OtherInterface>
    requires std::derived_from<OtherInterface, Interface>

        OtherInterface** GetAddressOf() noexcept
    {
        return static_cast<OtherInterface**>(&p_object);
    }

   public:
    template <typename OtherInterface>
    requires std::derived_from<OtherInterface, Interface>

        DDPtrHandle<OtherInterface> GetAddressOf()
    noexcept { return DDPtrHandle<OtherInterface>(*this); }

    template <typename OtherInterface>
    requires std::derived_from<OtherInterface, Interface>

        DDPtrHandle<OtherInterface> GetAddressOf()
    const noexcept { return DDPtrHandle<OtherInterface>(*this); }

    DDPtrHandle<Interface> operator&() noexcept { return GetAddressOf<Interface>(); }
    DDPtrHandle<Interface> operator&() const noexcept { return GetAddressOf<Interface>(); }
};
}  // namespace Toy::Engine