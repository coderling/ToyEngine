#pragma once
// http://diligentgraphics.com/diligent-engine/architecture/d3d12/variable-size-memory-allocations-manager/

#include <map>
#include <IAllocator.hpp>
#include "STDAllocator.hpp"


namespace Toy::Engine
{
	class VariableSizeAllocationsManager
	{
	public:
		using OffsetSizeType=size_t;
	private:
		struct FreeBlockInfo;

		using TFreeBlocksByOffsetMap = std::map<OffsetSizeType,
																				FreeBlockInfo,
																				std::less<OffsetSizeType>,
																				STDAllocatorRawMem<std::pair<const OffsetSizeType, FreeBlockInfo>>
																				>;
		using TFreeBlocksBySizeMap = std::multimap<OffsetSizeType,
																					  TFreeBlocksByOffsetMap::iterator,
																					  std::less<OffsetSizeType>,
																					  STDAllocatorRawMem<std::pair<const OffsetSizeType, TFreeBlocksByOffsetMap::iterator>>
																					>;

		struct FreeBlockInfo
		{
			OffsetSizeType size;

			TFreeBlocksBySizeMap::iterator order_size_it;

			FreeBlockInfo(OffsetSizeType size) :size(size) {}
		};

	public:
		VariableSizeAllocationsManager(OffsetSizeType max_size, IAllocator allocator);
		~VariableSizeAllocationsManager();
		VariableSizeAllocationsManager(VariableSizeAllocationsManager&& rhs) noexcept;
		VariableSizeAllocationsManager& operator=(VariableSizeAllocationsManager&& rhs) = default;

		// nocopy
		VariableSizeAllocationsManager(const VariableSizeAllocationsManager&) = delete;
		VariableSizeAllocationsManager& operator=(const VariableSizeAllocationsManager&) = delete;

	};

}