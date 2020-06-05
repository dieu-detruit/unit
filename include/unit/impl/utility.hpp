#pragma once

#include <complex>
#include <type_traits>

namespace Unit
{

#define ONLY_IF_IMPL(cond) std::enable_if_t<cond, std::nullptr_t> = nullptr
#define ONLY_IF(...) ONLY_IF_IMPL((__VA_ARGS__))

namespace Impl
{
constexpr std::size_t abs(std::size_t x)
{
    return x > 0 ? x : -x;
}
constexpr std::size_t gcd(std::size_t a, std::size_t b)
{
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    return abs(a) > abs(b) ? gcd(b, a % b) : gcd(a, b % a);
}
template <class... Args>
constexpr std::size_t gcd(std::size_t a, std::size_t b, Args... args)
{
    return gcd(gcd(a, b), args...);
}

template <class T>
struct is_complex : public std::false_type {
};
template <class T>
struct is_complex<std::complex<T>> : public std::true_type {
};

template <class T>
inline constexpr bool is_complex_v = is_complex<T>::value;

}  // namespace Impl

}  // namespace Unit
