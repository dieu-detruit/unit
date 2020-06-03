#pragma once

#include <type_traits>

#include "unit/impl/core.hpp"
#include "unit/impl/dimension.hpp"
#include "unit/impl/utility.hpp"

namespace Unit
{

// c * R
template <class dim, typename value_type, typename T, ONLY_IF(!Impl::is_complex_v<T> && !Impl::is_complex_v<value_type>)>
constexpr auto operator*(T c, DimensionType<dim, value_type> right)
{
    static_assert(std::is_convertible_v<value_type, T>, "You can only multiply value of a type convertible to value_type.");
    return DimensionType<dim, value_type>{c * right.value};
}

// c / R
template <class dim, typename value_type, typename T, ONLY_IF(!Impl::is_complex_v<T> && !Impl::is_complex_v<value_type>)>
constexpr auto operator/(T c, DimensionType<dim, value_type> right)
{
    static_assert(std::is_convertible_v<value_type, T>, "You can only multiply value of a type convertible to value_type.");
    return DimensionType<decltype(DimensionLess{} / dim{}), value_type>{c / right.value};
}

}  // namespace Unit
