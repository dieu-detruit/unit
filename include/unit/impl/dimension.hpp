#pragma once

#include <concepts>
#include <type_traits>

#include <unit/impl/utility.hpp>

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

struct DimBase {
};

template <long den, long... U>
struct Dim : DimBase {
private:
    static constexpr long g = Impl::gcd(den, U...);

public:
    // irreducible representation
    using irrep_type = Dim<den / g, (U / g)...>;

    template <long den_, long... U_>
    auto operator*(const Dim<den_, U_...>& rhs) const
        -> typename Dim<den * den_, (den_ * U + den * U_)...>::irrep_type
    {
        return {};
    }

    template <long den_, long... U_>
    auto operator/(const Dim<den_, U_...>& rhs) const
        -> typename Dim<den * den_, (den_ * U - den * U_)...>::irrep_type
    {
        return {};
    }

    template <long n>
    static auto pow()
        -> typename Dim<den, (U * n)...>::irrep_type
    {
        return {};
    }
    template <long d>
    static auto root()
        -> typename Dim<den * d, U...>::irrep_type
    {
        return {};
    }
};

using DimensionlessDim = Dim<1, 0, 0, 0, 0, 0, 0, 0>;

template <class T>
concept Dimensional = std::is_base_of_v<DimBase, T>;

template <class Dim>
concept Dimensionless = std::is_same_v<Dim, DimensionlessDim>;

template <class Dim>
concept Dimensionful = Dimensional<Dim> && not Dimensionless<Dim>;

namespace Impl
{
template <class T>
struct get_dimensions {
};

template <long den_, long L_, long M_, long T_, long Theta_, long N_, long I_, long J_>
struct get_dimensions<Dim<den_, L_, M_, T_, Theta_, N_, I_, J_>> {
    static constexpr long den = den_;
    static constexpr long L = L_;
    static constexpr long M = M_;
    static constexpr long T = T_;
    static constexpr long Theta = Theta_;
    static constexpr long N = N_;
    static constexpr long I = I_;
    static constexpr long J = J_;
};

}  // namespace Impl

}  // namespace Unit
