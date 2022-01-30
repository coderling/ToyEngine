#pragma once

#include <string>
#include "GPUResource.hpp"

namespace Toy::Graphics
{
	class UploadBuffer : public GPUResource
	{
	public:
		UploadBuffer(IDevice* device) :device(device) {}
		virtual ~UploadBuffer() { Destroy(); }

		void Create(const std::wstring& name, size_t size);

		void* Map(void);

		void UnMap(size_t begin = 0, size_t = -1);

		size_t GetBufferSize() { return buffer_size; }

	protected:
		size_t buffer_size;
		IDevice* device;
	};
}