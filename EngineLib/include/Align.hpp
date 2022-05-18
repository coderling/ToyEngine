#pragma once

#include <type_traits>

namespace Toy
{
	template<typename T>
	inline bool IsPowerOfTow(T val)
	{
		// �ж�һ�����Ƿ���2��n����
		// ���һ������2��n���ݣ���ô�����Ʊ�ʾ�±�Ȼֻ��һ��1��
		// ����8��1000 16��10000�ȣ���֮���Ȼ�ж��1����9��1001
		// ���ڽ�����ֵ��1�����Լ��������㣬��Ȼ����0�����磺0111 & 1000 = 0
		return val > 0 && (val & (val - 1)) == 0;
	}

	template<typename T1, typename T2>
	inline typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type AlignUp(T1 val, T2 alignment)
	{
		// ���ر�val��������ܱ�alignment��������
		// 1. T1,T2��������ͬ���������ͣ��漰��λ���㣬����λ����һ��
		// 2. ������ָ������
		// 3. alignmentΪ2��n����
		// 4. alignmentΪ2��n���ݣ���ô��������ʽֻ��һ��1����4��100��8��1000 ������
		//     ��ô(alignment -1)�����Ƶ�λ����1��4-1��011��8-1��0111��ȡ�����ǵ�λ����0����λʱ1��~(4-1):11...11100
		//	    ȡ����ȥ��ĳ����ֵ&����֤��λ��Ϊ0���������ܱ�alignment������Ҫȡ��val��ĵ�һ���ܱ�alignment������
		//     ����alignment-1���ɡ�
		static_assert(std::is_unsigned<T1>::value == std::is_unsigned<T2>::value, "both types must be signed or unsigned");
		static_assert(!std::is_pointer<T1>::value && !std::is_pointer<T2>::value, "types must not be pointers");
		using T = typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type;
		
		if (!IsPowerOfTow(alignment))
			return static_cast<T>(0);

		return (static_cast<T>(val) + static_cast<T>(alignment - 1)) & ~static_cast<T>(alignment - 1);
	}

	template<typename T1, typename T2>
	inline T1* AlignUp(T1* ptr, T2 alignment)
	{
		return reinterpret_cast<T1*>(AlignUp(reinterpret_cast<uintptr_t>(ptr), static_cast<uintptr_t>(alignment)));
	}
	
	template<typename T1, typename T2>
	inline typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type AlignDown(T1 val, T2 alignment)
	{
		// ���ر�val��������ܱ�alignment��������
		// 1. T1,T2��������ͬ���������ͣ��漰��λ���㣬����λ����һ��
		// 2. ������ָ������
		// 3. alignmentΪ2��n����
		// 4. alignmentΪ2��n���ݣ���ô��������ʽֻ��һ��1����4��100��8��1000 ������
		//     ��ô(alignment -1)�����Ƶ�λ����1��4-1��011��8-1��0111��ȡ�����ǵ�λ����0����λʱ1��~(4-1):11...11100
		//	    ȡ����ȥ��ĳ����ֵ&����֤��λ��Ϊ0���������ܱ�alignment������Ҫȡ��val��ĵ�һ���ܱ�alignment������
		//     ����alignment-1���ɡ�
		static_assert(std::is_unsigned<T1>::value == std::is_unsigned<T2>::value, "both types must be signed or unsigned");
		static_assert(!std::is_pointer<T1>::value && !std::is_pointer<T2>::value, "types must not be pointers");
		using T = typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type;
		
		if (!IsPowerOfTow(alignment))
			return static_cast<T>(0);

		return (static_cast<T>(val)) & ~static_cast<T>(alignment - 1);
	}

	template<typename T1, typename T2>
	inline T1* AlignDown(T1* ptr, T2 alignment)
	{
		return reinterpret_cast<T1*>(AlignDown(reinterpret_cast<uintptr_t>(ptr), static_cast<uintptr_t>(alignment)));
	}
}
