#pragma once

namespace Toy::Engine
{
class IRunTimeModule
{
   public:
    IRunTimeModule() = default;
    virtual ~IRunTimeModule() = default;

    virtual int Initialize() = 0;
    virtual void Tick() = 0;
    virtual void Finalize() = 0;
};
}  // namespace Toy::Engine