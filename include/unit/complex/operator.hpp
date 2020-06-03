#pragma once

#include "unit/complex/core.hpp"
#include "unit/impl/core.hpp"

#include <type_traits>

namespace Unit
{

// complex * real_dim_type
template <class dim, typename value_type, typename T, ONLY_IF(std::is_arithmetic_v<T>)>
constexpr auto operator*(std::complex<T> c, DimensionType<dim, value_type> right)
{
    static_assert(std::is_convertible_v<value_type, T>, "You can only multiply value of a type convertible to value_type.");
    return DimensionType<dim, std::complex<value_type>>{c * right.value};
}
// complex * complex_dim_type
template <class dim, typename value_type, typename T, ONLY_IF(std::is_arithmetic_v<T>)>
constexpr auto operator*(std::complex<T> c, DimensionType<dim, std::complex<value_type>> right)
{
    static_assert(std::is_convertible_v<value_type, T>, "You can only multiply value of a type convertible to value_type.");
    return DimensionType<dim, std::complex<value_type>>{c * right.value};
}

// complex / dim_type
template <class dim, typename value_type, typename T, ONLY_IF(std::is_arithmetic_v<T>)>
constexpr auto operator/(std::complex<T> c, DimensionType<dim, value_type> right)
{
    static_assert(std::is_convertible_v<value_type, T>, "You can only multiply value of a type convertible to value_type.");
    return DimensionType<decltype(DimensionLess{} / dim{}), value_type>{c / right.value};
}
// complex / complex_dim_type
template <class dim, typename value_type, typename T, ONLY_IF(std::is_arithmetic_v<T>)>
constexpr auto operator/(std::complex<T> c, DimensionType<dim, std::complex<value_type>> right)
{
    static_assert(std::is_convertible_v<value_type, T>, "You can only multiply value of a type convertible to value_type.");
    return DimensionType<decltype(DimensionLess{} / dim{}), std::complex<value_type>>{c / right.value};
}

}  // namespace Unit
