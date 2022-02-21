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
		void ExecuteCommandList(IGraphicsCommandList* cmd_list) override;
		void ExecuteCommandListSync(IGraphicsCommandList* cmd_list) override;
		void ExecuteCommandLists(std::size_t num, IGraphicsCommandList* const *cmd_list) override;
		void ExecuteCommandListsSync(std::size_t num,  IGraphicsCommandList* const *cmd_lists) override;
		void WaitGPU() override;
		void Destroy() override;

		GraphicsCommandQueue(const COMMAND_QUEUE_DESC* desc);
		GraphicsCommandQueue() = delete;

	private:
		ComPtr<IDeviceCommandQueue> common_queue;
	};
}

