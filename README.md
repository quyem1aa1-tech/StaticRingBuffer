# StaticRingBuffer

A lightweight, fixed-capacity circular buffer implemented in modern C++ (C++20). Designed for embedded systems and low-latency applications where dynamic memory allocation is strictly prohibited.

---

## 1. Project Goals

The main objectives of this mini-project are:

* **Zero Dynamic Allocation:** Build a ring buffer that operates purely on the stack or in static memory without calling `new` or `malloc`.
* **Practice Modern C++ (Chapters 1–3):** Apply key concepts from *Effective Modern C++*, including:
  * Type deduction rules and `decltype(auto)`.
  * Proper use of `auto` without dangling proxy references.
  * Modern idioms: `scoped enums` (`enum class`), `using` aliases, `constexpr`, and `noexcept`.
  * Safe member lifecycle management using `= default` and `= delete`.
* **Embedded-Ready Interface:** Provide deterministic runtime performance and compile-time verification via `static_assert`.

---

## 2. Problems to Solve

This project addresses several common issues in systems programming:

* **Buffer Overflow Control:**
  * Define explicit overflow behavior when the buffer is full.
  * Use a scoped enum (`enum class OverflowPolicy : uint8_t { Reject, Overwrite }`) to eliminate global namespace pollution and control memory overhead.
* **Accidental Object Copying:**
  * Returning elements via simple `auto` can cause unwanted deep copies.
  * Implement element access (`front()`, `back()`, `operator[]`) with `decltype(auto)` and correct references (`T&` / `const T&`) to preserve value categories.
* **Type Safety & Invalid Operations:**
  * Disable dangerous operations at compile time using `= delete` (e.g., assigning buffers of different capacities or using incompatible types).
  * Handle constructor ambiguities between `std::initializer_list` and capacity sizing.
* **Exception Safety & Compile-Time Execution:**
  * Mark core functions (`empty()`, `full()`, `size()`, `push()`, `pop()`) as `noexcept` so the compiler can generate optimized assembly.
  * Make index calculations and core access methods `constexpr` so data structures can be evaluated at compile time.
* **Loss of Move Semantics:**
  * Adhere to the *Rule of Zero* or *Rule of Five* so move constructors and assignments remain generated, fast, and `noexcept`.

---

## 3. Configuration & Requirements

### System Requirements
* **Language Standard:** C++20 (`-std=c++20`)
* **Build System:** CMake 3.20+ with Ninja or Make
* **Supported Compilers:**
  * GCC 11+
  * Clang 13+
  * MSVC 2019 (v16.11)+

### Build & Run
```bash
# 1. Configure the build directory
cmake -G Ninja -B build

# 2. Build the project
cmake --build build

# 3. Run the test suite
./build/tests/ring_buffer_tests
```