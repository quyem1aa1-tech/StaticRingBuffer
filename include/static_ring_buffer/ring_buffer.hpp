#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <utility>
#include <initializer_list>
#include <static_ring_buffer/overflow_policy.hpp>

namespace ring_buffer
{
    template <typename T, std::size_t Capacity, OverflowPolicy Policy = OverflowPolicy::Overwrite>

    class StaticRingBuffer
    {
    private:
        std::array<T, Capacity> data_{}; // Static array
        std::size_t head_{0};            // READ only
        std::size_t tail_{0};            // WRITE only
        std::size_t current_size_{0};    // Show current elements

    public:
        constexpr StaticRingBuffer() noexcept = default;
        constexpr StaticRingBuffer(std::initializer_list<T> init_list) noexcept
        {
            for (const auto &item : init_list)
            {
                (void)push(item);
            }
        }

        template <typename OtherT, std::size_t OtherCapacity, OverflowPolicy OtherPolicy>
        StaticRingBuffer &operator=(const StaticRingBuffer<OtherT, OtherCapacity, OtherPolicy> &) = delete;

        template <typename OtherT, std::size_t OtherCapacity, OverflowPolicy OtherPolicy>

        StaticRingBuffer(const StaticRingBuffer<OtherT, OtherCapacity, OtherPolicy> &) = delete;

        // [[nodiscard]] warns if the return value is discarded/ignored.
        // E.g., calling `buf.empty();` as a standalone statement -> WARNING

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return current_size_ == 0;
        }

        [[nodiscard]] constexpr bool full() const noexcept
        {
            return current_size_ == Capacity;
        }

        [[nodiscard]] constexpr std::size_t size() const noexcept
        {
            return current_size_;
        }

        [[nodiscard]] constexpr std::size_t capacity() const noexcept
        {
            return Capacity;
        }

        [[nodiscard]] constexpr bool push(const T &value) noexcept
        {
            if (full())
            {
                if constexpr (Policy == OverflowPolicy::Reject)
                {
                    return false;
                }

                else
                {
                    data_[tail_] = value;
                    tail_ = (1 + tail_) % Capacity;
                    head_ = (1 + head_) % Capacity;
                    return true;
                }
            }

            data_[tail_] = value;
            tail_ = (tail_ + 1) % Capacity;
            ++current_size_;
            return true;
        }

        [[nodiscard]] constexpr bool pop(T &value) noexcept
        {
            if (empty())
            {
                return false;
            }

            value = std::move(data_[head_]);
            head_ = (head_ + 1) % Capacity;
            --current_size_;

            return true;
        }
        [[nodiscard]] constexpr bool pop() noexcept
        {
            if (empty())
            {
                return false;
            }

            head_ = (head_ + 1) % Capacity;
            --current_size_;
            return true;
        }

        [[nodiscard]] constexpr T *front() noexcept
        {
            if (empty())
                return nullptr;
            return &data_[head_];
        }

        [[nodiscard]] constexpr const T *front() const noexcept
        {
            if (empty())
            {
                return nullptr;
            }

            return &data_[head_];
        }

        [[nodiscard]] constexpr T *back() noexcept
        {
            if (empty())
                return nullptr;
            const std::size_t back_index = (tail_ == 0) ? (Capacity - 1) : (tail_ - 1);
            return &data_[back_index];
        }
        [[nodiscard]] constexpr const T *back() const noexcept
        {
            if (empty())
            {
                return nullptr;
            }

            const std::size_t last_index = (tail_ == 0) ? (Capacity - 1) : (tail_ - 1);
            return &data_[last_index];
        }

        [[nodiscard]] constexpr T &operator[](std::size_t index) noexcept
        {
            assert(index < current_size_);

            std::size_t physical_index = (head_ + index) % Capacity;

            return data_[physical_index];
        }

        [[nodiscard]] constexpr const T &operator[](std::size_t index) const noexcept
        {
            assert(index < current_size_);

            std::size_t physical_index = (head_ + index) % Capacity;

            return data_[physical_index];
        }

        constexpr void clear() noexcept
        {
            head_ = 0;
            tail_ = 0;
            current_size_ = 0;
        }

        [[nodiscard]] constexpr bool push(T &&value) noexcept
        {
            if (full())
            {
                if (Policy == OverflowPolicy::Reject)
                {
                    return false;
                }
                else
                {
                    data_[tail_] = std::move(value);
                    tail_ = (tail_ + 1) % Capacity;
                    head_ = (head_ + 1) % Capacity;
                    return true;
                }
            }

            data_[tail_] = std::move(value);
            tail_ = (tail_ + 1) % Capacity;
            ++current_size_;

            return true;
        }
    };
}