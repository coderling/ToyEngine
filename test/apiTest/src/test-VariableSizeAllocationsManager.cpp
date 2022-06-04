#include <gtest/gtest.h>
#include <DefaultMemoryAllocator.hpp>
#include <VariableSizeAllocationsManager.hpp>

using namespace Toy::Engine;
TEST(VariableSizeAllocationsManager, Allocate_And_Free)
{
    using OffsetSizeType = VariableSizeAllocationsManager::OffsetSizeType;
    auto& allocator = DefaultMemoryAllocator::GetGobalAllocator();

    VariableSizeAllocationsManager alloc_mgr(128, allocator);
    EXPECT_EQ(alloc_mgr.FreeSize(), (OffsetSizeType)128);
    EXPECT_EQ(alloc_mgr.MaxSize(), (OffsetSizeType)128);
    EXPECT_EQ(alloc_mgr.UsedSize(), (OffsetSizeType)0);
    EXPECT_EQ(alloc_mgr.MaxFreeBlockSize(), (OffsetSizeType)128);

    auto alloc_1 = alloc_mgr.Allocate(15, 4);
    EXPECT_TRUE(alloc_1.IsValid());
    EXPECT_EQ(alloc_1.address_offset, (OffsetSizeType)0);
    EXPECT_EQ(alloc_1.size, (OffsetSizeType)16);
    EXPECT_EQ(alloc_mgr.UsedSize(), (OffsetSizeType)16);
    EXPECT_EQ(alloc_mgr.MaxFreeBlockSize(), (OffsetSizeType)(128 - 16));
    EXPECT_EQ(alloc_mgr.FreeSize(), (OffsetSizeType)(128 - 16));
    EXPECT_EQ(alloc_mgr.NumOfFreeBlocks(), (OffsetSizeType)(1));

    auto alloc_2 = alloc_mgr.Allocate(17, 8);
    EXPECT_TRUE(alloc_2.IsValid());
    EXPECT_EQ(alloc_2.address_offset, (OffsetSizeType)16);
    EXPECT_EQ(alloc_2.size, (OffsetSizeType)24);

    auto alloc_3 = alloc_mgr.Allocate(17, 2);
    EXPECT_TRUE(alloc_3.IsValid());
    EXPECT_EQ(alloc_3.address_offset, (OffsetSizeType)40);
    EXPECT_EQ(alloc_3.size, (OffsetSizeType)18);

    auto alloc_4 = alloc_mgr.Allocate(38, 4);
    EXPECT_TRUE(alloc_4.IsValid());
    EXPECT_EQ(alloc_4.address_offset, (OffsetSizeType)58);
    EXPECT_EQ(alloc_4.size, (OffsetSizeType)42);

    auto alloc_5 = alloc_mgr.Allocate(1, 4);
    EXPECT_TRUE(alloc_5.IsValid());
    EXPECT_EQ(alloc_5.address_offset, (OffsetSizeType)100);
    EXPECT_EQ(alloc_5.size, (OffsetSizeType)4);

    auto alloc_6 = alloc_mgr.Allocate(24, 2);
    EXPECT_TRUE(alloc_6.IsValid());
    EXPECT_EQ(alloc_6.address_offset, (OffsetSizeType)104);
    EXPECT_EQ(alloc_6.size, (OffsetSizeType)24);
    EXPECT_TRUE(alloc_mgr.IsFull());
    EXPECT_EQ(alloc_mgr.UsedSize(), (OffsetSizeType)128);
    EXPECT_EQ(alloc_mgr.FreeSize(), (OffsetSizeType)0);
    EXPECT_EQ(alloc_mgr.NumOfFreeBlocks(), (OffsetSizeType)0);

    alloc_mgr.Free(std::move(alloc_6));
    alloc_mgr.Free(std::move(alloc_1));
    EXPECT_EQ(alloc_mgr.FreeSize(), (OffsetSizeType)(16 + 24));
    EXPECT_EQ(alloc_mgr.NumOfFreeBlocks(), (OffsetSizeType)(2));
    EXPECT_EQ(alloc_mgr.MaxFreeBlockSize(), (OffsetSizeType)(24));
    alloc_mgr.Free(std::move(alloc_2));
    EXPECT_EQ(alloc_mgr.FreeSize(), (OffsetSizeType)(16 + 24 + 24));
    EXPECT_EQ(alloc_mgr.NumOfFreeBlocks(), (OffsetSizeType)(2));
    EXPECT_EQ(alloc_mgr.MaxFreeBlockSize(), (OffsetSizeType)(40));
    alloc_mgr.Free(std::move(alloc_4));
    EXPECT_EQ(alloc_mgr.FreeSize(), (OffsetSizeType)(16 + 24 + 24 + 42));
    EXPECT_EQ(alloc_mgr.NumOfFreeBlocks(), (OffsetSizeType)(3));
    EXPECT_EQ(alloc_mgr.MaxFreeBlockSize(), (OffsetSizeType)(42));
    alloc_mgr.Free(std::move(alloc_3));
    alloc_mgr.Free(std::move(alloc_5));
    EXPECT_TRUE(alloc_mgr.IsEmpty());
    EXPECT_EQ(alloc_mgr.NumOfFreeBlocks(), (OffsetSizeType)1);
    EXPECT_EQ(alloc_mgr.MaxFreeBlockSize(), (OffsetSizeType)128);
    EXPECT_EQ(alloc_mgr.FreeSize(), (OffsetSizeType)128);
    EXPECT_EQ(alloc_mgr.UsedSize(), (OffsetSizeType)0);

    VariableSizeAllocationsManager alloc_mgr2(128, allocator);

    // extend
    auto alloc_7 = alloc_mgr2.Allocate(129, 1);
    EXPECT_FALSE(alloc_7.IsValid());
    EXPECT_EQ(alloc_7.address_offset, VariableSizeAllocationsManager::Allocation::InvalidAddressOffset);
    EXPECT_EQ(alloc_7.size, (OffsetSizeType)0);

    alloc_mgr2.Extend(128);
    EXPECT_EQ(alloc_mgr2.MaxSize(), (OffsetSizeType)256);
    EXPECT_EQ(alloc_mgr2.FreeSize(), (OffsetSizeType)256);
    EXPECT_EQ(alloc_mgr2.NumOfFreeBlocks(), (OffsetSizeType)1);

    auto alloc_8 = alloc_mgr2.Allocate(100, 1);
    EXPECT_TRUE(alloc_8.IsValid());
    EXPECT_EQ(alloc_8.address_offset, (OffsetSizeType)0);
    EXPECT_EQ(alloc_8.size, (OffsetSizeType)100);
    auto alloc_9 = alloc_mgr2.Allocate(56, 1);
    auto alloc_10 = alloc_mgr2.Allocate(100, 1);
    alloc_mgr2.Free(alloc_9.address_offset, alloc_9.size);
    EXPECT_EQ(alloc_mgr2.FreeSize(), (OffsetSizeType)56);
    EXPECT_EQ(alloc_mgr2.NumOfFreeBlocks(), (OffsetSizeType)1);
    alloc_mgr2.Extend(128);
    EXPECT_EQ(alloc_mgr2.FreeSize(), (OffsetSizeType)(56 + 128));
    EXPECT_EQ(alloc_mgr2.NumOfFreeBlocks(), 2);
    EXPECT_EQ(alloc_mgr2.MaxFreeBlockSize(), 128);

    alloc_mgr2.Free(std::move(alloc_8));
    alloc_mgr2.Free(std::move(alloc_10));
    EXPECT_TRUE(alloc_mgr2.IsEmpty());
    EXPECT_EQ(alloc_mgr2.NumOfFreeBlocks(), (OffsetSizeType)1);
    EXPECT_EQ(alloc_mgr2.MaxFreeBlockSize(), (OffsetSizeType)(128 * 3));
    EXPECT_EQ(alloc_mgr2.FreeSize(), (OffsetSizeType)(128 * 3));
    EXPECT_EQ(alloc_mgr2.UsedSize(), (OffsetSizeType)0);
}

TEST(VariableSizeAllocationsManager, FreeOrder)
{
    using OffsetSizeType = VariableSizeAllocationsManager::OffsetSizeType;
    auto& allocator = DefaultMemoryAllocator::GetGobalAllocator();
    const size_t alloc_count = 6;
    VariableSizeAllocationsManager::Allocation allocations[alloc_count];
    int release_order[alloc_count];
    for (size_t index = 0; index < alloc_count; ++index)
        {
            release_order[index] = index;
        }

    size_t num_do = 0;
    do
        {
            ++num_do;
            VariableSizeAllocationsManager alloc_mgr(alloc_count * 4, allocator);
            for (size_t i = 0; i < alloc_count; ++i)
                {
                    allocations[i] = alloc_mgr.Allocate(4, 1);
                    EXPECT_EQ(allocations[i].address_offset, 4 * i);
                    EXPECT_EQ(allocations[i].size, 4);
                }

            for (size_t i = 0; i < alloc_count; ++i)
                {
                    alloc_mgr.Free(std::move(allocations[release_order[i]]));
                }

            EXPECT_TRUE(alloc_mgr.IsEmpty());
            EXPECT_EQ(alloc_mgr.NumOfFreeBlocks(), (OffsetSizeType)1);
            EXPECT_EQ(alloc_mgr.MaxFreeBlockSize(), (OffsetSizeType)(alloc_count * 4));
            EXPECT_EQ(alloc_mgr.FreeSize(), (OffsetSizeType)(alloc_count * 4));
            EXPECT_EQ(alloc_mgr.UsedSize(), (OffsetSizeType)0);
    } while (std::next_permutation(std::begin(release_order), std::end(release_order)));
    EXPECT_EQ(num_do, 720);
}