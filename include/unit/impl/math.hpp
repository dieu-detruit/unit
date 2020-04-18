#pragma once

#include <cmath>

#include "unit/impl/quantity.hpp"

namespace Unit
{

_unit_value_type sin(const DimensionLessType& x)
{
    return std::sin(x.value);
}

_unit_value_type cos(const DimensionLessType& x)
{
    return std::cos(x.value);
}

_unit_value_type tan(const DimensionLessType& x)
{
    return std::tan(x.value);
}

}  // namespace Unit
