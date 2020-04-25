#pragma once

namespace Unit
{

/*
 * Dimension of SI Base Units
 * 
 * L :      Length
 * M :      Mass
 * T :      Time
 * Theta :  Thermodynamic Temeprature
 * N :      Amount of Substances
 * I :      Current
 * J :      Luminous Intensity
 *
 */

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


/* 
 * Struct to express the dimension
 *
 *  template parameter:
 *      - den
 *          - denominator
 *      - L, M, T, Theta, N, I, J
 *          - dimension for each base unit
 *  example:
 *      - m^2 = Dim<1, 2, 0, 0, 0, 0, 0, 0>
 *      - m^(1/2)s^(2/3) = m^(3/6)s^(4/6) = Dim<6, 3, 0, 4, 0, 0, 0, 0>
 * 
 */
template <int den, int... U>
struct Dim {
private:
    static constexpr int g = Impl::gcd(den, U...);

public:
    // irreducible representation
    using irrep_type = Dim<den / g, (U / g)...>;

    template <int den_, int... U_>
    auto operator*(const Dim<den_, U_...>& rhs)
        -> typename Dim<den * den_, (den_ * U + den * U_)...>::irrep_type
    {
        return {};
    }

    template <int den_, int... U_>
    auto operator/(const Dim<den_, U_...>& rhs)
        -> typename Dim<den * den_, (den_ * U - den * U_)...>::irrep_type
    {
        return {};
    }
};

template <int n_>
struct pow_exponent {
    static constexpr int n = n_;
};
template <int d_>
struct pow_exponent_inv {
    static constexpr int d = d_;
};

template <class ex, int n = ex::n, int... U>
auto pow(Dim<U...>, ex)
    -> typename Dim<(U * n)...>::irrep_type
{
}
template <class ex, int d = ex::d, int... U>
auto pow(Dim<U...>, ex)
    -> typename Dim<(U / d)...>::irrep_type
{
}


using DimensionLess = Dim<1, 0, 0, 0, 0, 0, 0, 0>;

namespace Impl
{
template <class T>
struct get_dimensions {
};

template <int den_, int L_, int M_, int T_, int Theta_, int N_, int I_, int J_>
struct get_dimensions<Dim<den_, L_, M_, T_, Theta_, N_, I_, J_>> {
    static constexpr int den = den_;
    static constexpr int L = L_;
    static constexpr int M = M_;
    static constexpr int T = T_;
    static constexpr int Theta = Theta_;
    static constexpr int N = N_;
    static constexpr int I = I_;
    static constexpr int J = J_;
};

}  // namespace Impl

}  // namespace Unit
