#pragma once

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
template <std::size_t den, std::size_t... U>
struct Dim {
private:
    static constexpr std::size_t g = Impl::gcd(den, U...);

public:
    // irreducible representation
    using irrep_type = Dim<den / g, (U / g)...>;

    template <std::size_t den_, std::size_t... U_>
    auto operator*(const Dim<den_, U_...>& rhs) const
        -> typename Dim<den * den_, (den_ * U + den * U_)...>::irrep_type
    {
        return {};
    }

    template <std::size_t den_, std::size_t... U_>
    auto operator/(const Dim<den_, U_...>& rhs) const
        -> typename Dim<den * den_, (den_ * U - den * U_)...>::irrep_type
    {
        return {};
    }

    template <std::size_t n>
    static auto pow()
        -> typename Dim<den, (U * n)...>::irrep_type
    {
        return {};
    }
    template <std::size_t d>
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

template <std::size_t den_, std::size_t L_, std::size_t M_, std::size_t T_, std::size_t Theta_, std::size_t N_, std::size_t I_, std::size_t J_>
struct get_dimensions<Dim<den_, L_, M_, T_, Theta_, N_, I_, J_>> {
    static constexpr std::size_t den = den_;
    static constexpr std::size_t L = L_;
    static constexpr std::size_t M = M_;
    static constexpr std::size_t T = T_;
    static constexpr std::size_t Theta = Theta_;
    static constexpr std::size_t N = N_;
    static constexpr std::size_t I = I_;
    static constexpr std::size_t J = J_;
};

template <class T>
struct is_dimensionless : std::false_type {
};
template <>
struct is_dimensionless<DimensionLess> : std::true_type {
};

template <class T>
inline constexpr bool is_dimensionless_v = is_dimensionless<T>::value;

}  // namespace Impl

}  // namespace Unit
