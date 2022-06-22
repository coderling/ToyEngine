#include "SpinLock.hpp"

#if defined(_MSC_VER) && ((_M_IX86_FP >= 2) || defined(_M_X64))
#include <emmintrin.h>
#define PAUSE _mm_pause
#elif (defined(__clang__) || defined(__GNUC__)) && (defined(__i386__) || defined(__x86_64__))
#define PAUSE __builtin_ia32_pause
#else
#define PAUSE()
#endif

namespace Toy::Threading
{
void Spinlock::Pause() noexcept { Pause(); }
}  // namespace Toy::Threading