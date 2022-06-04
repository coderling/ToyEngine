#include "VariableSizeAllocationsManager.hpp"
#include "STDAllocator.hpp"

using namespace Toy::Engine;

VariableSizeAllocationsManager::VariableSizeAllocationsManager(const OffsetSizeType& max_size, IAllocator& allocator)
    : free_block_by_offset(
          STD_ALLOCATOR_RAWMEM(TFreeBlocksByOffsetMap::value_type, allocator, "allocation for map<OffsetSizeType, FreeBlockInfo>")),
      free_block_by_size(STD_ALLOCATOR_RAWMEM(TFreeBlocksBySizeMap::value_type, allocator,
                                              "allocation for multimap<OffsetSizeType, "
                                              "TFreeBlocksByOffsetMap::iterator>")),
      free_size(max_size),
      max_size(max_size)
{
    AddNewBlock(0, max_size);
    ResetCurrentAlignment();
#if ENGINE_DEBUG
    DebugAllocation();
#endif
}

VariableSizeAllocationsManager::~VariableSizeAllocationsManager()
{
#if ENGINE_DEBUG
    // when destroy must single block and size is max_size;
    ENGINE_ASSERT(free_block_by_offset.size() == 1, "must free all allocation");
    ENGINE_ASSERT(free_block_by_offset.size() == free_block_by_size.size(), "size of two map must equal!");
    ENGINE_ASSERT(free_block_by_offset.begin()->first == 0, "single block offset must to be 0");
    ENGINE_ASSERT(free_block_by_offset.begin()->second.size == max_size, "single block size must to be ", max_size);
    ENGINE_ASSERT_EXPR(free_block_by_offset.begin()->second.order_size_it == free_block_by_size.begin());

    ENGINE_ASSERT(free_block_by_size.begin()->first == max_size, "single block size must to be ", max_size);
    ENGINE_ASSERT(free_block_by_size.begin()->second == free_block_by_offset.begin(), "error iterator");
#endif
}

VariableSizeAllocationsManager::VariableSizeAllocationsManager(VariableSizeAllocationsManager&& rhs) noexcept
    : free_block_by_size(std::move(rhs.free_block_by_size)),
      free_block_by_offset(std::move(rhs.free_block_by_offset)),
      max_size(rhs.max_size),
      free_size(rhs.free_size),
      current_alignment(rhs.current_alignment)
{
    rhs.max_size = 0;
    rhs.free_size = 0;
    rhs.current_alignment = 0;
}

VariableSizeAllocationsManager::Allocation VariableSizeAllocationsManager::Allocate(const OffsetSizeType& size,
                                                                                    const OffsetSizeType& alignment)
{
    ENGINE_ASSERT_EXPR(size > 0);
    ENGINE_ASSERT_EXPR(IsPowerOfTow(alignment), "alignment (", alignment, ") must be power of 2");
    const auto& rsize = AlignUp(size, alignment);
    if (free_size < rsize)
        {
            return Allocation::InvalidAllocation();
        }

    const auto& alignment_diff = (alignment > current_alignment) ? alignment - current_alignment : 0;
    auto lower_bound_iter_iter = free_block_by_size.lower_bound((rsize + alignment_diff));
    if (lower_bound_iter_iter == free_block_by_size.end())
        {
            return Allocation::InvalidAllocation();
        }

    auto lower_bound_iter = lower_bound_iter_iter->second;
    ENGINE_ASSERT_EXPR(lower_bound_iter->second.size >= rsize + alignment_diff);
    ENGINE_ASSERT_EXPR(lower_bound_iter->second.size == lower_bound_iter_iter->first);
    ENGINE_ASSERT_EXPR(lower_bound_iter->second.order_size_it == lower_bound_iter_iter);
    // block:
    //    |---------------------block.size----------------------|
    //    |------size+aligned_size---------|------new_size------|
    // offset             new_offset
    // remove old block, add new block size equal (block.size - size)
    // and make new_offset align by alignment
    auto offset = lower_bound_iter->first;
    ENGINE_ASSERT_EXPR(offset % current_alignment == 0);
    auto aligned_offset = AlignUp(offset, alignment);
    auto final_size = rsize + (aligned_offset - offset);
    ENGINE_ASSERT_EXPR(final_size <= rsize + alignment_diff);
    auto new_offset = offset + final_size;
    auto new_size = lower_bound_iter->second.size - final_size;
    free_block_by_size.erase(lower_bound_iter_iter);
    free_block_by_offset.erase(lower_bound_iter);
    if (new_size > 0)
        {
            AddNewBlock(new_offset, new_size);
        }

    free_size -= final_size;

    if ((rsize & (current_alignment - 1)) != 0)
        {
            if (IsPowerOfTow(rsize))
                {
                    ENGINE_ASSERT_EXPR(rsize >= alignment && size < current_alignment);
                    current_alignment = rsize;
                }
            else
                {
                    current_alignment = std::min(alignment, current_alignment);
                }
        }

#if ENGINE_DEBUG
    DebugAllocation();
#endif
    return Allocation{offset, final_size};
}

void VariableSizeAllocationsManager::Free(Allocation&& allocation)
{
    ENGINE_ASSERT_EXPR(allocation.IsValid());
    Free(allocation.address_offset, allocation.size);
    allocation = {};
}

void VariableSizeAllocationsManager::Free(const OffsetSizeType& offset, const OffsetSizeType& size)
{
    ENGINE_ASSERT_EXPR(offset + size <= max_size && offset != Allocation::InvalidAddressOffset);

    auto next_block_iter = free_block_by_offset.upper_bound(offset);
#ifdef ENGINE_DEBUG
    auto l_next_block_iter = free_block_by_offset.lower_bound(offset);
    // since zero allocations are not allowed, lower_bound always equal to upper_bound
    ENGINE_ASSERT_EXPR(next_block_iter == l_next_block_iter);
#endif
    // check overlap with nextblock
    ENGINE_ASSERT_EXPR(next_block_iter == free_block_by_offset.end() || offset + size <= next_block_iter->first);
    auto pre_block_iter = next_block_iter;
    if (pre_block_iter != free_block_by_offset.begin())
        {
            --pre_block_iter;
            // check overlap with preblock
            ENGINE_ASSERT_EXPR(pre_block_iter->first + pre_block_iter->second.size <= offset);
        }
    else
        {
            pre_block_iter = free_block_by_offset.end();
        }

    OffsetSizeType new_offset, new_size;
    if (pre_block_iter != free_block_by_offset.end() && pre_block_iter->first + pre_block_iter->second.size == offset)
        {
            // combine to preblock
            new_offset = pre_block_iter->first;
            new_size = pre_block_iter->second.size + size;
            if (next_block_iter != free_block_by_offset.end() && offset + size == next_block_iter->first)
                {
                    // combine to nextblock
                    new_size += next_block_iter->second.size;
                    // erase block iter from size map
                    free_block_by_size.erase(pre_block_iter->second.order_size_it);
                    free_block_by_size.erase(next_block_iter->second.order_size_it);
                    ++next_block_iter;
                    // range delete from offset map
                    free_block_by_offset.erase(pre_block_iter, next_block_iter);
                }
            else
                {
                    // erase block iter from siz map
                    free_block_by_size.erase(pre_block_iter->second.order_size_it);
                    // erase block from offset map
                    free_block_by_offset.erase(pre_block_iter);
                }
        }
    else if (next_block_iter != free_block_by_offset.end() && offset + size == next_block_iter->first)
        {
            // combine to nextblock
            new_offset = offset;
            new_size = size + next_block_iter->second.size;
            // erase block item from size map
            free_block_by_size.erase(next_block_iter->second.order_size_it);
            // erase nextblock from offset map
            free_block_by_offset.erase(next_block_iter);
        }
    else
        {
            new_offset = offset;
            new_size = size;
        }

    AddNewBlock(new_offset, new_size);

    free_size += size;
    if (IsEmpty())
        {
            ENGINE_ASSERT_EXPR(NumOfFreeBlocks() == 1);
            ResetCurrentAlignment();
        }

#ifdef ENGINE_DEBUG
    DebugAllocation();
#endif
}

bool VariableSizeAllocationsManager::IsFull() const { return free_size == 0; }

bool VariableSizeAllocationsManager::IsEmpty() const { return free_size == max_size; }

VariableSizeAllocationsManager::OffsetSizeType VariableSizeAllocationsManager::MaxSize() const { return max_size; }

VariableSizeAllocationsManager::OffsetSizeType VariableSizeAllocationsManager::FreeSize() const { return free_size; }

VariableSizeAllocationsManager::OffsetSizeType VariableSizeAllocationsManager::UsedSize() const { return max_size - free_size; }

VariableSizeAllocationsManager::OffsetSizeType VariableSizeAllocationsManager::NumOfFreeBlocks() const
{
    return free_block_by_offset.size();
}

VariableSizeAllocationsManager::OffsetSizeType VariableSizeAllocationsManager::MaxFreeBlockSize() const
{
    return free_block_by_size.empty() ? 0 : free_block_by_size.rbegin()->first;
}

void VariableSizeAllocationsManager::Extend(const OffsetSizeType& extend_size)
{
    ENGINE_ASSERT_EXPR(extend_size > 0);
    OffsetSizeType new_offset = max_size;
    OffsetSizeType new_size = extend_size;
    // if has last block
    if (!free_block_by_offset.empty())
        {
            auto last_iter = free_block_by_offset.end();
            --last_iter;
            auto last_offset = last_iter->first;
            auto last_size = last_iter->second.size;
            if (last_offset + last_size == max_size)
                {
                    new_offset = last_offset;
                    new_size = last_size + extend_size;
                    ENGINE_ASSERT_EXPR(last_iter->second.order_size_it->first == last_size &&
                                       last_iter->second.order_size_it->second == last_iter);
                    // combine to last_iter
                    free_block_by_size.erase(last_iter->second.order_size_it);
                    free_block_by_offset.erase(last_iter);
                }
        }

    AddNewBlock(new_offset, new_size);

    max_size += extend_size;
    free_size += extend_size;

#ifdef ENGINE_DEBUG
    DebugAllocation();
#endif
}

#ifdef ENGINE_DEBUG
void VariableSizeAllocationsManager::DebugAllocation()
{
    OffsetSizeType total_free_size = 0;
    // current_alignment is power of 2
    ENGINE_ASSERT_EXPR(IsPowerOfTow(current_alignment));
    // size of two map must equal
    ENGINE_ASSERT_EXPR(free_block_by_size.size() == free_block_by_offset.size());

    auto block_iter = free_block_by_offset.begin();
    auto pre_block_iter = free_block_by_offset.end();
    while (block_iter != free_block_by_offset.end())
        {
            // offset + size <= max_size && size > 0
            ENGINE_ASSERT_EXPR(block_iter->first + block_iter->second.size <= max_size);
            // offset must be aligned by current_alignment
            ENGINE_ASSERT_EXPR((block_iter->first & (current_alignment - 1)) == 0,
                               "block offset must be aligned by current_alignment:", current_alignment);
            if (block_iter->second.size + block_iter->first < max_size)
                {
                    // all block sizes except for the last must be aligned by current_alignment
                    ENGINE_ASSERT_EXPR((block_iter->second.size & (current_alignment - 1)) == 0, "all block size(", block_iter->first, ",",
                                       block_iter->second.size,
                                       ") except for the last must be aligned by current_alignment:", current_alignment);
                }
            // block refrence by size map
            ENGINE_ASSERT_EXPR(block_iter == block_iter->second.order_size_it->second);
            // block size equal size map iterator->first
            ENGINE_ASSERT_EXPR(block_iter->second.size == block_iter->second.order_size_it->first);
            // check block overlap
            ENGINE_ASSERT_EXPR(
                pre_block_iter == free_block_by_offset.end() || block_iter->first >= pre_block_iter->first + pre_block_iter->second.size,
                "blocks are overlap");
            pre_block_iter = block_iter;
            ++block_iter;
        }

    auto order_size_iter = free_block_by_size.begin();
    while (order_size_iter != free_block_by_size.end())
        {
            // check size equal offset
            ENGINE_ASSERT_EXPR(order_size_iter->first == order_size_iter->second->second.size);
            total_free_size += order_size_iter->first;
            ++order_size_iter;
        }

    ENGINE_ASSERT_EXPR(total_free_size == free_size);
}
#endif

void VariableSizeAllocationsManager::AddNewBlock(const OffsetSizeType& offset, const OffsetSizeType& size)
{
    auto block_iter = free_block_by_offset.emplace(offset, FreeBlockInfo(size));
    ENGINE_ASSERT_EXPR(block_iter.second);
    auto order_size_iter = free_block_by_size.emplace(size, block_iter.first);
    block_iter.first->second.order_size_it = order_size_iter;
}

void VariableSizeAllocationsManager::ResetCurrentAlignment()
{
    current_alignment = 1;
    while (current_alignment * 2 < max_size)
        {
            current_alignment *= 2;
        }
}