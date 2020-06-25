#pragma once

#include <cmath>

#include <type_traits>
#include <unit/impl/core.hpp>
#include <unit/impl/dimension.hpp>
#include <unit/impl/types.hpp>

namespace std
{

#define DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION(func)             \
    template <Unit::Dimensionful dim_t>                           \
    Unit::DimensionType<dim_t> func(Unit::DimensionType<dim_t> x) \
    {                                                             \
        return Unit::DimensionType<dim_t>{std::func(x.value)};    \
    }


#define DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(func)                                          \
    template <Unit::Dimensionful dim_t>                                                         \
    Unit::DimensionType<dim_t> func(Unit::DimensionType<dim_t> x, Unit::DimensionType<dim_t> y) \
    {                                                                                           \
        return Unit::DimensionType<dim_t>{std::func(x.value, y.value)};                         \
    }

#define DECLARE_HOMOGENIUS_TERNARY_CMATH_FUNCTION(func)                                                                       \
    template <Unit::Dimensionful dim_t>                                                                                       \
    Unit::DimensionType<dim_t> func(Unit::DimensionType<dim_t> x, Unit::DimensionType<dim_t> y, Unit::DimensionType<dim_t> z) \
    {                                                                                                                         \
        return Unit::DimensionType<dim_t>{std::func(x.value, y.value, z.value)};                                              \
    }


template <Unit::Dimensionful dim_t>
auto atan2(Unit::DimensionType<dim_t> x, Unit::DimensionType<dim_t> y)
{
    return Unit::Angle{std::atan2(x.value, y.value)};
}

// root and abs
template <Unit::Dimensionful dim_t>
auto sqrt(Unit::DimensionType<dim_t> x)
{
    return x.sqrt();
}
template <Unit::Dimensionful dim_t>
auto cbrt(Unit::DimensionType<dim_t> x)
{
    return x.cbrt();
}
DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(hypot);
DECLARE_HOMOGENIUS_TERNARY_CMATH_FUNCTION(hypot);
DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION(abs);
DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION(fabs);

// neiborhood integral number
DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION(ceil);
DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION(floor);
DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION(trunc);
DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION(round);

// modulo
DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(fmod);
DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(remainder);

// utility for floating point
DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(copysign);
DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(nextafter);

// max min
DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(fmax);
DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(fmin);
DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(fdim);

// sign
template <Unit::Dimensionful dim_t>
bool signbit(Unit::DimensionType<dim_t> x)
{
    return std::signbit(x.value);
}
template <Unit::Dimensionful x_dim_t, Unit::Dimensionful y_dim_t>
bool signbit(Unit::DimensionType<x_dim_t> x, Unit::DimensionType<y_dim_t> y)
{
    return Unit::DimensionType<x_dim_t>{std::copysign(x.value, y.value)};
}

#undef DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION
#undef DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION
#undef DECLARE_HOMOGENIUS_TERNARY_CMATH_FUNCTION

}  // namespace std
