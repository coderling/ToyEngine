#pragma once
#include <stdint.h>

#define NODISCARD [[nodiscard]]
#define NODISCARD_MSG(msg) [[nodiscard(msg)]]

#define NOCOPY_INPLACE(CLS_NAME)                                                                                                           \
    CLS_NAME(const CLS_NAME&) = delete;                                                                                                    \
    CLS_NAME& operator=(const CLS_NAME&) = delete

#define NOMOVE_INPLACE(CLS_NAME)                                                                                                           \
    CLS_NAME(CLS_NAME&&) = delete;                                                                                                         \
    CLS_NAME& operator=(CLS_NAME&&) = delete

#define NOCOPY_AND_NOMOVE(CLS_NAME)                                                                                                        \
    NOCOPY_INPLACE(CLS_NAME);                                                                                                              \
    NOMOVE_INPLACE(CLS_NAME)

#if _MSC_VER
#define ENGINE_FUNCTION_CALL_CONVENTION __cdecl
#else
#define ENGINE_FUNCTION_CALL_CONVENTION
#endif

enum TOY_RESULT
{
    TR_ERROR = -1,
    TR_OK = 0
};