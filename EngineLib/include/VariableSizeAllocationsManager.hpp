#pragma once
// http://diligentgraphics.com/diligent-engine/architecture/d3d12/variable-size-memory-allocations-manager/

#include <Align.hpp>
#include <DebugUtility.hpp>
#include <IAllocator.hpp>
#include <Logger.hpp>
#include <map>
#include "STDAllocator.hpp"

namespace Toy::Engine
{
class TOY_LIB_API VariableSizeAllocationsManager
{
   public:
    using OffsetSizeType = size_t;

   private:
    struct FreeBlockInfo;

    using TFreeBlocksByOffsetMap = std::map<OffsetSizeType, FreeBlockInfo, std::less<OffsetSizeType>,
                                            STDAllocatorRawMem<std::pair<const OffsetSizeType, FreeBlockInfo>>>;
    using TFreeBlocksBySizeMap = std::multimap<OffsetSizeType, TFreeBlocksByOffsetMap::iterator, std::less<OffsetSizeType>,
                                               STDAllocatorRawMem<std::pair<const OffsetSizeType, TFreeBlocksByOffsetMap::iterator>>>;

    struct FreeBlockInfo
    {
        OffsetSizeType size;

        TFreeBlocksBySizeMap::iterator order_size_it;

        FreeBlockInfo(OffsetSizeType size) : size(size) {}
    };

   public:
    VariableSizeAllocationsManager(const OffsetSizeType& max_size, IAllocator& allocator);

    ~VariableSizeAllocationsManager();

    // move construct
    VariableSizeAllocationsManager(VariableSizeAllocationsManager&& rhs) noexcept;
    // move assign construct
    VariableSizeAllocationsManager& operator=(VariableSizeAllocationsManager&& rhs) = default;

    // nocopy
    VariableSizeAllocationsManager(const VariableSizeAllocationsManager&) = delete;
    VariableSizeAllocationsManager& operator=(const VariableSizeAllocationsManager&) = delete;

    //
    struct Allocation
    {
       public:
        Allocation(OffsetSizeType offset, OffsetSizeType size) : address_offset(offset), size(size) {}

        Allocation() {}

        static constexpr OffsetSizeType InvalidAddressOffset = ~OffsetSizeType{0};
        static Allocation InvalidAllocation() { return Allocation{InvalidAddressOffset, 0}; }

        bool IsValid() const { return address_offset != InvalidAddressOffset; }

        bool operator==(const Allocation& rhs) const { return this->address_offset == rhs.address_offset && this->size == rhs.size; }

        OffsetSizeType address_offset = InvalidAddressOffset;
        OffsetSizeType size = 0;
    };

    Allocation Allocate(const OffsetSizeType& size, const OffsetSizeType& alignment);

    void Free(Allocation&& allocation);

    void Free(const OffsetSizeType& offset, const OffsetSizeType& size);

    bool IsFull() const;
    bool IsEmpty() const;
    OffsetSizeType MaxSize() const;
    OffsetSizeType FreeSize() const;
    OffsetSizeType UsedSize() const;
    size_t NumOfFreeBlocks() const;
    OffsetSizeType MaxFreeBlockSize() const;

    void Extend(const OffsetSizeType& extend_size);

#ifdef ENGINE_DEBUG
    void DebugAllocation();
#endif
   private:
    void AddNewBlock(const OffsetSizeType& offset, const OffsetSizeType& size);
    void ResetCurrentAlignment();

   private:
    TFreeBlocksByOffsetMap free_block_by_offset;
    TFreeBlocksBySizeMap free_block_by_size;
    OffsetSizeType free_size;
    OffsetSizeType max_size;
    OffsetSizeType current_alignment;
};

}  // namespace Toy::Engine