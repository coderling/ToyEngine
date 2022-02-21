#pragma once

namespace Toy::Engine
{
	struct NoCopy
	{
		NoCopy() = default; // Ĭ�Ϲ��캯��
		NoCopy(const NoCopy&) = delete; // ��������
		NoCopy& operator=(const NoCopy&) = delete; // ������ֵ
	};

	class IObject
	{
	public:
		virtual ~IObject() {};
		virtual void Destroy() = 0;
	};
}