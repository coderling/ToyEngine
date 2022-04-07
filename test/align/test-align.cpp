#include <iostream>
#include <stdint.h>
#include <gtest/gtest.h>
#include <Align.hpp>

using namespace Toy;

TEST(Align, IsPowerOfTow)
{
	for (std::uint32_t i = 0; i < 256; ++i)
    {
        bool IsPw2 = (i == 1 || i == 2 || i == 4 || i == 8 || i == 16 || i == 32 || i == 64 || i == 128);
        EXPECT_EQ(IsPowerOfTow(static_cast<std::uint8_t>(i)), IsPw2);
        EXPECT_EQ(IsPowerOfTow(static_cast<std::uint16_t>(i)), IsPw2);
        EXPECT_EQ(IsPowerOfTow(i), IsPw2);
    }
}
