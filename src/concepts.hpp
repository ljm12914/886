#pragma once
#include <concepts>
#include <cstdint>
#include <type_traits>

namespace Util {
    typedef int8_t i8;
    typedef int16_t i16;
    typedef int32_t i32;
    typedef int64_t i64;
    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
    using std::enable_if_t, std::decay_t, std::is_same_v, std::constructible_from, std::convertible_to;

    template <typename T>
    concept SInt = is_same_v<T, i8> || is_same_v<T, i16> || is_same_v<T, i32> || is_same_v<T, i64>;

    template <typename T>
    concept UInt = is_same_v<T, u8> || is_same_v<T, u16> || is_same_v<T, u32> || is_same_v<T, u64>;

    template <typename T>
    concept Int = SInt<T> || UInt<T>;

    template <typename T>
    concept FP = is_same_v<T, float> || is_same_v<T, double>;

    template <typename T, typename U>
    concept equal = is_same_v<decay_t<T>, U>;

    template <typename T, typename... Us>
    concept one_of = (is_same_v<decay_t<T>, Us> || ...);

    template <typename T, typename... Us>
    concept all_is = (is_same_v<decay_t<T>, Us> && ...);

    template <typename T, typename U>
    concept like = constructible_from<U, T> || convertible_to<T, U>;
}