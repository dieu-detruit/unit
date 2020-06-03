#pragma once

#include <type_traits>

namespace Unit
{

#define ONLY_IF_IMPL(cond) std::enable_if_t<cond, std::nullptr_t> = nullptr
#define ONLY_IF(...) ONLY_IF_IMPL((__VA_ARGS__))

namespace Impl
{
constexpr int abs(int x)
{
    return x > 0 ? x : -x;
}
constexpr int gcd(int a, int b)
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
constexpr int gcd(int a, int b, Args... args)
{
    return gcd(gcd(a, b), args...);
}

}  // namespace Impl

}  // namespace Unit
