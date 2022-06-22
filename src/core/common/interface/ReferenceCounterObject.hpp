#include <concepts>
#include "IAllocator.hpp"
#include "IObject.hpp"
#include "ReferenceCounter.hpp"

namespace Toy::Engine
{

template <typename Interface>
requires std::derived_from<Interface, IObject>
class ReferenceCounterObject : public Interface
{
    ReferenceCounter* p_refcounter;

   public:
    template <typename... InterfaceArgsType>
    ReferenceCounterObject(IReferenceCounter* _p_refcounter, InterfaceArgsType&&... args) noexcept
        : Interface(std::forward<InterfaceArgsType>(args)...),
          p_refcounter(StaticCheckPointerCast<ReferenceCounter, IReferenceCounter>(_p_refcounter))
    {
    }

    ~ReferenceCounterObject() override {}

   protected:
    inline long ENGINE_FUNCTION_CALL_CONVENTION AddReference() override final
    {
        ENGINE_ASSERT_EXPR(p_refcounter != nullptr);
        p_refcounter->AddStrongRef();
    }

    inline long ENGINE_FUNCTION_CALL_CONVENTION Release() override final
    {
        ENGINE_ASSERT_EXPR(p_refcounter != nullptr);
        p_refcounter->ReleaseStrongRef();
    }

    inline IReferenceCounter* GetReferenceCounter() override final { return p_refcounter; }

   private:
    friend class ReferenceCounter;
    template <typename ObjectType, typename AllocatorType>
    friend class MakeReferenceCounter;

    // private overload  delete and new, so only access by MakeReferenceCounter
    void* operator new(std::size_t size) { return new uint8_t[size]; }
    void operator delete(void* ptr) { delete[] reinterpret_cast<uint8_t*>(ptr); }

    template <typename AllocatorType>
    void* operator new(std::size_t size, AllocatorType* allocator, const char* description, const char* filename, const char* line)
    {
        return allocator->Allocate(size, description, filename, line);
    }

    template <typename AllocatorType>
    void operator delete(void* ptr, AllocatorType* allocator, const char* description, const char* filename, const char* line)
    {
        allocator->Free(ptr, description, filename, line);
    }
};

template <typename ObjectType, typename AllocatorType = IAllocator>
class MakeReferenceCounter
{
    AllocatorType* p_allocator;

#ifdef ENGINE_DEVELOPMENT
    const char* description;
    const char* filename;
    const char* line;
#endif
   public:
    MakeReferenceCounter(AllocatorType& _p_allocator, const char* _description, const char* _filename, const char* _line) noexcept
        : p_allocator(_p_allocator)
#ifdef ENGINE_DEVELOPMENT
          ,
          description(_description),
          filename(_filename),
          line(_line)
#endif
    {
    }

    NOCOPY_AND_NOMOVE(MakeReferenceCounter);

    template <typename... ObjectArgsType>
    ObjectType* operator()(ObjectArgsType&&... args)
    {
#ifndef ENGINE_DEVELOPMENT
        static constexpr const char* description = "<Unavailable in release build>";
        static constexpr const char* filename = "<Unavailable in release build>";
        static constexpr int linenumber = -1;
#endif

        // handle expection
        ReferenceCounter* p_refcounter = new ReferenceCounter();
        ObjectType* p_obj = nullptr;
        try
            {
                if (p_allocator == nullptr)
                    {
                        p_obj = new ObjectType(p_refcounter, std::forward<ObjectArgsType>()...);
                    }
                else
                    {
                        p_obj = new (p_allocator, description, filename, line) ObjectType(p_refcounter, std::forward<ObjectArgsType>()...);
                    }
                p_refcounter->Attach(p_obj, p_allocator);
            }
        catch (...)
            {
                // when expection , delete reference
                // In addition, p_refcounter will be delete when refrence counter become 0 and after target object release
                if (p_refcounter != nullptr)
                    {
                        p_refcounter->DeleteSelf();
                        p_refcounter = nullptr;
                    }
            }
        return p_obj;
    }
};

#define MAKE_REF_OBJECT(ObjectType, allocator, description, ...)                                                                           \
    MakeReferenceCounter<ObjectType, typename std::remove_reference<decltype(allocator)>::type>(allocator, description, __FILE__,          \
                                                                                                __LINE__, ##__VA_ARGS__)
}  // namespace Toy::Engine