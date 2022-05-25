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

TEST(Align, AlignUp)
{
    EXPECT_EQ(AlignUp(std::uint32_t(0), std::uint32_t(8)), std::uint32_t(0));
    EXPECT_EQ(AlignUp(std::uint32_t(1), std::uint32_t(8)), std::uint32_t(8));
    EXPECT_EQ(AlignUp(std::uint32_t(9), std::uint32_t(8)), std::uint32_t(16));
    EXPECT_EQ(AlignUp(std::uint8_t(9), std::uint32_t(1024)), std::uint32_t(1024));
    EXPECT_EQ(AlignUp(std::uint32_t(1025), std::uint64_t(1024)), std::uint32_t(2048));
    EXPECT_EQ(AlignUp(std::uint32_t(1025), std::uint32_t(1024)), std::uint32_t(2048));
    EXPECT_EQ(AlignUp((std::uint64_t(1) << 63) + 1, std::uint32_t(1024)), (std::uint64_t(1) << 63) + 1024);
    for (std::uint32_t i = 0; i < 1024; ++i)
    {
        constexpr std::uint32_t alignment = 16;
        std::uint32_t aligned = (i / alignment) * alignment;
        if (aligned < i)
        {
            aligned += alignment;
        }

        EXPECT_EQ(AlignUp(i, alignment), aligned);
    }
}

TEST(Align, AlignDown)
{
    EXPECT_EQ(AlignDown(std::uint32_t(0), std::uint32_t(8)), std::uint32_t(0));
    EXPECT_EQ(AlignDown(std::uint32_t(1), std::uint32_t(8)), std::uint32_t(0));
    EXPECT_EQ(AlignDown(std::uint32_t(9), std::uint32_t(8)), std::uint32_t(8));
    EXPECT_EQ(AlignDown(std::uint8_t(7), std::uint32_t(1024)), std::uint32_t(0));
    EXPECT_EQ(AlignDown(std::uint32_t(1025), std::uint64_t(1024)), std::uint32_t(1024));
    EXPECT_EQ(AlignDown(std::uint32_t(1025), std::uint32_t(1024)), std::uint32_t(1024));
    EXPECT_EQ(AlignDown((std::uint64_t(1) << 63) + std::uint64_t(1022), std::uint32_t(1024)), std::uint64_t(1) << 63);
    for (std::uint32_t i = 0; i < 1024; ++i)
    {
        constexpr std::uint32_t alignment = 16;
        std::uint32_t aligned = (i / alignment) * alignment;
        EXPECT_EQ(AlignDown(i, alignment), aligned);
    }
}

TEST(Align, AlignUpPtr)
{
    EXPECT_EQ(AlignUp((void*)0x1000, std::uint32_t(16)), (void*)0x1000);
    EXPECT_EQ(AlignUp((void*)0x1001, std::uint32_t(16)), (void*)0x1010);
    EXPECT_EQ(AlignUp((void*)0x1010, std::uint32_t(16)), (void*)0x1010);
    EXPECT_EQ(AlignUp((void*)0x101F, std::uint32_t(16)), (void*)0x1020);

    for (size_t i = 0; i < 1024; ++i)
    {
        constexpr std::uint32_t alignment = 16;
        size_t aligned = (i / alignment) * alignment;
        if (aligned < i)
        {
            aligned += alignment;
        }
        auto ptr_aligned = (void*)(0x1000 + aligned);
        EXPECT_EQ(AlignUp((void*)(0x1000 + i), (size_t)alignment), ptr_aligned);
    }
}

TEST(Align, AlignDownPtr)
{
    EXPECT_EQ(AlignDown((void*)0x1000, std::uint32_t(16)), (void*)0x1000);
    EXPECT_EQ(AlignDown((void*)0x1001, std::uint32_t(16)), (void*)0x1000);
    EXPECT_EQ(AlignDown((void*)0x1010, std::uint32_t(16)), (void*)0x1010);
    EXPECT_EQ(AlignDown((void*)0x101F, std::uint32_t(16)), (void*)0x1010);

    for (size_t i = 0; i < 1024; ++i)
    {
        constexpr std::uint32_t alignment = 16;
        size_t aligned = (i / alignment) * alignment;
        auto ptr_aligned = (void*)(0x1000 + aligned);
        EXPECT_EQ(AlignDown((void*)(0x1000 + i), (size_t)alignment), ptr_aligned);
    }
}

TEST(Align, AlignUpNonPow2)
{
    EXPECT_EQ(AlignUpNonPow2(0, 5), 0);
    EXPECT_EQ(AlignUpNonPow2(std::uint16_t(15), std::uint16_t(6)), std::uint16_t(18));
    EXPECT_EQ(AlignUpNonPow2(std::uint32_t(19), std::uint16_t(15)), std::uint32_t(30));
    EXPECT_EQ(AlignUpNonPow2(std::uint64_t(19), std::uint64_t(1115)), std::uint64_t(1115));
    EXPECT_EQ(AlignUpNonPow2(std::uint64_t(1119), std::uint64_t(1115)), std::uint64_t(2230));
    EXPECT_EQ(AlignUpNonPow2((std::uint64_t(1) << 63) + 1, std::uint64_t(1024)), (std::uint64_t(1) << 63) + 1024);

    for (size_t i = 0; i < 1024; ++i)
    {
        constexpr size_t alignment = 15;
        size_t aligned = i + alignment - 1;
        aligned = aligned - aligned % alignment;
        EXPECT_EQ(AlignUpNonPow2(i, alignment), aligned);
    }
}

TEST(Align, AlignDownNonPow2)
{
    EXPECT_EQ(AlignDownNonPow2(0, 5), 0);
    EXPECT_EQ(AlignDownNonPow2(std::uint16_t(15), std::uint16_t(6)), std::uint16_t(12));
    EXPECT_EQ(AlignDownNonPow2(std::uint32_t(19), std::uint16_t(15)), std::uint32_t(15));
    EXPECT_EQ(AlignDownNonPow2(std::uint64_t(19), std::uint64_t(1115)), std::uint64_t(0));
    EXPECT_EQ(AlignDownNonPow2(std::uint64_t(1119), std::uint64_t(1115)), std::uint64_t(1115));
    EXPECT_EQ(AlignDownNonPow2((std::uint64_t(1) << 63) + 1, std::uint64_t(1024)), (std::uint64_t(1) << 63));

    for (size_t i = 0; i < 1024; ++i)
    {
        constexpr size_t alignment = 15;
        size_t aligned = i - i % alignment;
        EXPECT_EQ(AlignDownNonPow2(i, alignment), aligned);
    }
}
