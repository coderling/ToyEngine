#define EXPORT_DLL
#include "Time.hpp"
int main()
{
    auto pf_gtimer = Toy::Engine::TEngine_LoadGetTimer();
    auto timer = pf_gtimer();
    auto now = timer.ElapsedTimef();
    while (timer.ElapsedTimef() - now < 10)
        {
        }
    printf("end ten sceonds!!!");
    return 0;
}