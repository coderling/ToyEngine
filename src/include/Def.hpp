#pragma once

namespace Toy
{
	struct NoCopy
	{
		NoCopy() = default; // Ĭ�Ϲ��캯��
		virtual ~NoCopy() {};
		NoCopy(const NoCopy&) = delete; // ��������
		NoCopy& operator=(const NoCopy&) = delete; // ������ֵ
	};
}