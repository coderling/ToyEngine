#pragma once

namespace Toy::Engine
{
	struct NoCopy
	{
		NoCopy() = default; // 默认构造函数
		NoCopy(const NoCopy&) = delete; // 不允许拷贝
		NoCopy& operator=(const NoCopy&) = delete; // 不允许赋值
	};

	class IObject
	{
	public:
		virtual ~IObject() {};
		virtual void Destroy() = 0;
	};
}