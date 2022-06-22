#pragma once
#include <stdint.h>
#include <vcruntime_string.h>

namespace Toy
{
struct IUUID
{
    uint32_t d1;
    uint16_t d2;
    uint16_t d3;
    uint8_t array[8];

    bool operator==(const IUUID& rhs) const
    {
        return d1 == rhs.d1 && d2 == rhs.d2 && d3 == rhs.d3 && memcmp(array, rhs.array, sizeof(array));
    }
};

static constexpr const IUUID UUID_UNKNOWN = {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}};
}  // namespace Toy