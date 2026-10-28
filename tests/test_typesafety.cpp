#include <iostream>
#include <type_traits>
#include "static_ring_buffer/ring_buffer.hpp"

using ring_buffer::OverflowPolicy;
using ring_buffer::StaticRingBuffer;

constexpr bool test_compile_time_ring_buffer()
{
    ring_buffer::StaticRingBuffer<int, 3, ring_buffer::OverflowPolicy::Overwrite> buf;

    (void)buf.push(10);
    (void)buf.push(20);
    (void)buf.push(30);
    (void)buf.push(40);

    if (buf.size() != 3)
        return false;
    if (*buf.front() != 20)
        return false;
    if (*buf.back() != 40)
        return false;

    (void)buf.pop();
    if (*buf.front() != 30 || buf.size() != 2)
        return false;

    return true;
}

static_assert(test_compile_time_ring_buffer(),
              "Compile-time execution for push/pop/overwrite failed!");

int main()
{
    using BufInt5_Reject = StaticRingBuffer<int, 5, OverflowPolicy::Reject>;
    using BufInt10_Reject = StaticRingBuffer<int, 10, OverflowPolicy::Reject>;
    using BufDouble5_Reject = StaticRingBuffer<double, 5, OverflowPolicy::Reject>;
    using BufInt5_Overwrite = StaticRingBuffer<int, 5, OverflowPolicy::Overwrite>;

    // 1. Identical types MUST be copy constructible and assignable
    static_assert(std::is_copy_constructible_v<BufInt5_Reject>,
                  "Design error: Buffers of identical types must be copy constructible!");
    static_assert(std::is_copy_assignable_v<BufInt5_Reject>,
                  "Design error: Buffers of identical types must be copy assignable!");

    // 2. Different capacities -> MUST BE DISABLED
    static_assert(!std::is_constructible_v<BufInt5_Reject, const BufInt10_Reject &>,
                  "Type safety violation: Buffers with different capacities must not be copy constructible!");
    static_assert(!std::is_assignable_v<BufInt5_Reject &, const BufInt10_Reject &>,
                  "Type safety violation: Buffers with different capacities must not be copy assignable!");

    // 3. Different element types -> MUST BE DISABLED
    static_assert(!std::is_assignable_v<BufInt5_Reject &, const BufDouble5_Reject &>,
                  "Type safety violation: Buffers with incompatible element types must not be assignable!");

    // 4. Different overflow policies -> MUST BE DISABLED
    static_assert(!std::is_assignable_v<BufInt5_Reject &, const BufInt5_Overwrite &>,
                  "Type safety violation: Buffers with different overflow policies must not be assignable!");

    // 5. Runtime check for initializer list support
    BufInt5_Overwrite buf_list = {10, 20, 30};
    if (buf_list.size() == 3 && *buf_list.front() == 10 && *buf_list.back() == 30)
    {
        std::cout << "[PASS] Initializer list functionality verified successfully!\n";
    }

    std::cout << "[PASS] All type safety constraints and compile-time assertions passed!\n";
    return 0;
}