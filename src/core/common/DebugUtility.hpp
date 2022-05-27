#pragma

#include <FormatString.hpp>
#include <iostream>
#include <cassert>

namespace Toy::Debug
{
#ifdef ENGINE_DEBUG 
#define ENGINE_ASSERT_FAILED(msg, ...)                          \
do                                                              \
	{                                                           \
		const auto amsg = Toy::FormatString(msg, ##__VA_ARGS__);\
		std::cerr << "[Assert] Fail in " << __FILE__            \
                << " Function " << __FUNCTION__                 \
                <<  " Line " << __LINE__                        \
                << ":" << amsg << std::endl;                    \
		abort();                                                \
	}while(false)


#define ENGINE_ASSERT(expr, msg, ...)                           \
do                                                              \
	{                                                           \
		if(!(expr))                                             \
		{                                                       \
			ENGINE_ASSERT_FAILED(msg, ##__VA_ARGS__);           \
		}                                                       \
	} while(false)

#define ENGINE_ASSERT_EXPR(expr)                                \
do                                                              \
	{                                                           \
		ENGINE_ASSERT(expr, "check exppr:{} failed", #expr);    \
	}while(false)
#else
#define ENGINE_ASSERT_FAILED(msg, ...) do{}while(false)
#define ENGINE_ASSERT_EXPR(expr, msg, ...) do{}while(false)
#define ENGINE_ASSERT(expr) do{}while(false)
#endif // ENGINE_DEBUG
}