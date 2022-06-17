#pragma once
#include "pch.hpp"

namespace Toy::Engine
{
struct TOY_LIB_API NoCopy
{
    NoCopy() = default;                         // 默认构造函数
    NoCopy(const NoCopy&) = delete;             // 不允许拷贝
    NoCopy& operator=(const NoCopy&) = delete;  // 不允许赋值
};

class TOY_LIB_API IObject
{
   public:
    virtual ~IObject()
    {
        if (!is_destroy)
            {
                Destroy();
            }
    };
    void Destroy()
    {
        is_destroy = true;
        OnDestroy();
    }

   protected:
    virtual void OnDestroy() = 0;

   private:
    bool is_destroy = false;
};
}  // namespace Toy::Engine