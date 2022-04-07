#pragma once
#include <wrl.h>

#include "IGraphicsCommandQueue.hpp"

using namespace Microsoft::WRL;

namespace Toy::Graphics
{
	class GraphicsCommandQueue  final : public IGraphicsCommandQueue
	{
	public:
		IDeviceCommandQueue* GetDeviceQueue() const noexcept override { return common_queue.Get(); }
		void ExecuteCommandList(const IGraphicsCommandList* cmd_list) override;
		void ExecuteCommandListSync(const IGraphicsCommandList* cmd_list) override;
		void ExecuteCommandLists(const std::size_t& num, const IGraphicsCommandList* const *cmd_list) override;
		void ExecuteCommandListsSync(const std::size_t& num,  const IGraphicsCommandList* const *cmd_lists) override;
		void Signal(std::uint64_t fence_value) override;

		GraphicsCommandQueue(const COMMAND_QUEUE_DESC* desc, ID3D12Fence* fence);
		GraphicsCommandQueue() = delete;
	protected:
		void OnDestroy() override;
	private:
		ComPtr<IDeviceCommandQueue> common_queue;
		ID3D12Fence* fence;
	};
}

