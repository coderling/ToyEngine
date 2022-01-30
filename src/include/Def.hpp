#pragma once

namespace Toy
{
	struct NoCopy
	{
		NoCopy() = default; // 默认构造函数
		virtual ~NoCopy() {};
		NoCopy(const NoCopy&) = delete; // 不允许拷贝
		NoCopy& operator=(const NoCopy&) = delete; // 不允许赋值
	};
}