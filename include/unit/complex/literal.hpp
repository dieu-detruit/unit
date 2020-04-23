#pragma once

#include "unit/complex/core.hpp"
#include "unit/complex/operator.hpp"
#include "unit/impl/core.hpp"

namespace Unit
{

inline constexpr auto operator""_i(long double value)
{
    return Complex<DimensionLessType>{_unit_value_type{0}, static_cast<_unit_value_type>(value)};
}

inline constexpr auto operator""_j(long double value)
{
    return Complex<DimensionLessType>{_unit_value_type{0}, static_cast<_unit_value_type>(value)};
}

}  // namespace Unit
