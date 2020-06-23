#pragma once

#include <complex>
#include <type_traits>

namespace Unit
{

namespace Impl
{
constexpr long abs(long x)
{
    return x > 0 ? x : -x;
}
constexpr long gcd(long a, long b)
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
constexpr long gcd(long a, long b, Args... args)
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
