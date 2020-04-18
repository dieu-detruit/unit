#pragma once

#include <type_traits>

#include "unit/impl/core.hpp"
#include "unit/impl/dimension.hpp"
#include "unit/impl/type_traits.hpp"

namespace Unit
{

// c * R
template <class dim, typename value_type, typename T, ONLY_IF(std::is_arithmetic_v<T>)>
constexpr auto operator*(T c, DimensionType<dim, value_type> right)
{
    static_assert(is_multiplicable_v<value_type, T>, "You can only multiply floating point value.");
    return DimensionType<dim, value_type>{c * right.value};
}

// c / R
template <class dim, typename value_type, typename T, ONLY_IF(std::is_arithmetic_v<T>)>
constexpr auto operator/(T c, DimensionType<dim, value_type> right)
{
    static_assert(is_multiplicable_v<value_type, T>, "You can only devide with floating point value.");
    return DimensionType<decltype(DimensionLess{} / dim{}), value_type>{c / right.value};
}

}  // namespace Unit
