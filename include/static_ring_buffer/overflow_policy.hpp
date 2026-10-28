#pragma once
#include <cstdint>

namespace ring_buffer
{
    enum class OverflowPolicy : uint8_t
    {
        Overwrite,
        Reject
    };

    
}