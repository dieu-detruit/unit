#pragma once

#include "unit/impl/utility.hpp"

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
    auto operator*(const Dim<den_, U_...>& rhs) const
        -> typename Dim<den * den_, (den_ * U + den * U_)...>::irrep_type
    {
        return {};
    }

    template <int den_, int... U_>
    auto operator/(const Dim<den_, U_...>& rhs) const
        -> typename Dim<den * den_, (den_ * U - den * U_)...>::irrep_type
    {
        return {};
    }

    template <int n>
    static auto pow()
        -> typename Dim<den, (U * n)...>::irrep_type
    {
        return {};
    }
    template <int d>
    static auto root()
        -> typename Dim<den * d, U...>::irrep_type
    {
        return {};
    }
};

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
