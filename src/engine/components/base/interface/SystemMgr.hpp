#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "CommonDefines.hpp"
#include "RefCountPtr.hpp"


namespace Toy::Engine
{
class ISystem;
class SystemMgr final
{
   private:
    std::unordered_map<uintptr_t, RefCountPtr<ISystem>> systems;
    std::unordered_map<IUUID, uintptr_t> system_cached;

    NOCOPY_AND_NOMOVE(SystemMgr);

   public:
    static SystemMgr Instance();
    int Initialize();
    void Tick();
    void Finalize();

    template <typename SystemType>
    requires std::derived_from<SystemType, ISystem> SystemType* GetSystem()
    {
        auto u_ptr = system_cached.find(SystemType::CLS_UUID);
        if (u_ptr != system_cached.end())
            {
                auto sys_iter = systems.find(u_ptr->second);
                ENGINE_ASSERT_EXPR(sys_iter != systems.end(), "can not find cached system");
                return sys_iter->second.template RawPtr<SystemType>();
            }

        // no cached make new one
        auto system_ptr = MakeReferenceCounter<SystemType>()();
        uintptr_t uint_ptr = reinterpret_cast<uintptr_t>(system_ptr);
        auto system_ref_ptr = RefCountPtr<ISystem>(system_ptr);
        systems.emplace(uint_ptr, std::move(system_ref_ptr));
        system_cached.emplace(SystemType::CLS_UUID, uint_ptr);
        system_ptr->Initialize();

        ENGINE_ASSERT_EXPR(system_ref_ptr.GetNumOfStrongRef() == 1 && system_ref_ptr.GetNumOfWeakRef() == 0);
        return system_ptr;
    }
};
}  // namespace Toy::Engine