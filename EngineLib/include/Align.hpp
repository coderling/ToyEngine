#pragma once

#include <type_traits>

namespace Toy
{
	template<typename T>
	inline bool IsPowerOfTow(T val)
	{
		// 判断一个数是否是2的n次幂
		// 如果一个数是2的n次幂，那么二进制表示下必然只有一个1，
		// 例如8：1000 16：10000等，反之则必然有多个1，入9：1001
		// 现在将该数值减1再与自己进行运算，必然等于0，例如：0111 & 1000 = 0
		return val > 0 && (val & (val - 1)) == 0;
	}

	template<typename T1, typename T2>
	inline typename std::conditional<sizeof(T1) >= sizeof(T2), T1, T2>::type AlignUp(T1 val, T2 alignment)
	{
		// 返回比val大的最少能被alignment整除的数
		// 1. T1,T2必须是相同的数据类型，涉及到位运算，符号位保持一致
		// 2. 不能是指针类型
		// 3. alignment为2的n次幂
		// 4. alignment为2的n次幂，那么二进制形式只有一个1，如4：100，8：1000 。。。
		//     那么(alignment -1)二进制低位都是1，4-1：011，8-1：0111，取反则是低位都是0，高位时1，~(4-1):11...11100
		//	    取反后，去与某个数值&，保证低位都为0，这样就能被alignment整除。要取比val大的第一个能被alignment整除的
		//     加上alignment-1即可。
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
		// 返回比val大的最少能被alignment整除的数
		// 1. T1,T2必须是相同的数据类型，涉及到位运算，符号位保持一致
		// 2. 不能是指针类型
		// 3. alignment为2的n次幂
		// 4. alignment为2的n次幂，那么二进制形式只有一个1，如4：100，8：1000 。。。
		//     那么(alignment -1)二进制低位都是1，4-1：011，8-1：0111，取反则是低位都是0，高位时1，~(4-1):11...11100
		//	    取反后，去与某个数值&，保证低位都为0，这样就能被alignment整除。要取比val大的第一个能被alignment整除的
		//     加上alignment-1即可。
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
