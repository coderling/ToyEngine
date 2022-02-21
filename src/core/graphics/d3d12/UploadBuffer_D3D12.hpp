#pragma once

#include <string>
#include "GPUResource_D3D12.hpp"
#include "IUploadBuffer.hpp"

namespace Toy::Graphics
{
	class UploadBuffer : public GPUResource, public IUploadBuffer
	{
	public:
		UploadBuffer(IDevice* device) :device(device), buffer_size(0) {}
		virtual ~UploadBuffer() { Destroy(); }

		void Create(const std::wstring& name, size_t size) override;

		void* Map(void) override;

		void UnMap(size_t begin = 0, size_t = -1) override;

		size_t GetBufferSize() noexcept override { return buffer_size; }

	protected:
		size_t buffer_size;
		IDevice* device;
	};
}