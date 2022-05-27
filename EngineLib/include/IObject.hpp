#pragma once
#include <pch.hpp>

namespace Toy::Engine
{
	struct  TOY_LIB_API  NoCopy
	{
		NoCopy() = default; // Ĭ�Ϲ��캯��
		NoCopy(const NoCopy&) = delete; // ��������
		NoCopy& operator=(const NoCopy&) = delete; // ������ֵ
	};

	class TOY_LIB_API IObject
	{
	public:
		virtual ~IObject() 
		{
			if (!is_destroy)
			{
				Destroy();
			}
		};
		void Destroy()
		{
			is_destroy = true;
			OnDestroy();
		}
	protected:
		virtual void OnDestroy() = 0;
	private:
		bool is_destroy = false;
	};
}