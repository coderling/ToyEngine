#include <gtest/gtest.h>
#include <Time.hpp>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    auto timer = Toy::Engine::Timer();
    auto now = timer.ElapsedTimef();
    while (false)
        // while (timer.ElapsedTimef() - now < 10)
        {
        }
    auto ret = RUN_ALL_TESTS();
    std::cout << "\n";
    return ret;
}