#pragma once
#include <chrono>

namespace Toy::Engine
{
class Timer final
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