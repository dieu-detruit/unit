#include <cmath>

#include <type_traits>
#include <unit/impl/core.hpp>
#include <unit/impl/dimension.hpp>
#include <unit/impl/types.hpp>

namespace std
{

#define DECLARE_HOMOGENIUS_UNARY_CMATH_FUNCTION(func)                          \
    template <class dim_t, ONLY_IF(not Unit::Impl::is_dimensionless_v<dim_t>)> \
    auto func(Unit::DimensionType<dim_t> x)                                    \
    {                                                                          \
        return Unit::DimensionType<dim_t>{std::func(x.value)};                 \
    }


#define DECLARE_HOMOGENIUS_BINARY_CMATH_FUNCTION(func)                         \
    template <class dim_t, ONLY_IF(not Unit::Impl::is_dimensionless_v<dim_t>)> \
    auto func(Unit::DimensionType<dim_t> x, Unit::DimensionType<dim_t> y)      \
    {                                                                          \
        return Unit::DimensionType<dim_t>{std::func(x.value, y.value)};        \
    }

#define DECLARE_HOMOGENIUS_TERNARY_CMATH_FUNCTION(func)                                                 \
    template <class dim_t, ONLY_IF(not Unit::Impl::is_dimensionless_v<dim_t>)>                          \
    auto func(Unit::DimensionType<dim_t> x, Unit::DimensionType<dim_t> y, Unit::DimensionType<dim_t> z) \
    {                                                                                                   \
        return Unit::DimensionType<dim_t>{std::func(x.value, y.value, z.value)};                        \
    }


template <class dim_t, ONLY_IF(not Unit::Impl::is_dimensionless_v<dim_t>)>
auto atan2(Unit::DimensionType<dim_t> x, Unit::DimensionType<dim_t> y)
{
    return Unit::Angle{std::atan2(x.value, y.value)};
}

// root and abs
template <class dim_t, ONLY_IF(not Unit::Impl::is_dimensionless_v<dim_t>)>
auto sqrt(Unit::DimensionType<dim_t> x)
{
    return x.sqrt();
}
template <class dim_t, ONLY_IF(not Unit::Impl::is_dimensionless_v<dim_t>)>
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


#undef DECLARE_HOMOGENIUS_ARG_CMATH_FUNCTION
}  // namespace std
