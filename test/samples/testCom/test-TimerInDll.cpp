
#define EXPORT_DLL
#include "Time.hpp"
int main()
{
    auto timer = Toy::Engine::Timer();
    auto now = timer.ElapsedTimef();
    while (timer.ElapsedTimef() - now < 10)
        {
        }
    printf("end ten sceonds!!!");
    return 0;
}