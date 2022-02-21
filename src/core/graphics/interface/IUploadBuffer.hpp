#pragma once

namespace Toy::Graphics
{
	class IUploadBuffer 
	{
	public:
		virtual void Create(const std::wstring& name, size_t size) = 0;

		virtual void* Map(void) = 0;

		virtual void UnMap(size_t begin = 0, size_t = -1) = 0;

		virtual size_t GetBufferSize() = 0;
	};
}