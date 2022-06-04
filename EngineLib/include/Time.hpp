#pragma once
#include <chrono>
#include <pch.hpp>

namespace Toy::Engine
{
class TOY_LIB_API Timer final
{
   public:
    Timer() noexcept;
    void Reset();
    double ElapsedTime();
    float ElapsedTimef();

   private:
    std::chrono::high_resolution_clock::time_point start_time;
};
}  // namespace Toy::Engine