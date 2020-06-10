#pragma once

#include <complex>
#include <type_traits>

#include <unit/complex/core.hpp>
#include <unit/complex/types.hpp>
#include <unit/impl/types.hpp>
#include <unit/impl/utility.hpp>

namespace std
{

template <class dim_t>
inline auto real(const Unit::DimensionType<dim_t, Unit::_complex_unit_value_type>& x)
{
    return x.real();
}
template <class dim_t>
inline auto imag(const Unit::DimensionType<dim_t, Unit::_complex_unit_value_type>& x)
{
    return x.imag();
}
template <class dim_t>
inline auto conj(const Unit::DimensionType<dim_t, Unit::_complex_unit_value_type>& x)
{
    return x.conj();
}
template <class dim_t>
inline auto arg(const Unit::DimensionType<dim_t, Unit::_complex_unit_value_type>& x)
{
    return x.arg();
}
template <class dim_t>
inline auto norm(const Unit::DimensionType<dim_t, Unit::_complex_unit_value_type>& x)
{
    return x.norm();
}
template <class dim_t>
inline auto abs(const Unit::DimensionType<dim_t, Unit::_complex_unit_value_type>& x)
{
    return x.abs();
}

inline auto polar(const Unit::DimensionLessType norm, Unit::Phase phase)
{
    return Unit::Complex<Unit::DimensionLessType>{std::polar(norm.value, phase.value)};
}

template <class dim_type, ONLY_IF(not std::is_same_v<dim_type, Unit::Phase>)>
inline auto polar(dim_type norm, Unit::Phase phase)
{
    return Unit::Complex<dim_type>{std::polar(norm.value, phase.value)};
}

inline auto polar(const Unit::_unit_value_type norm, Unit::Phase phase)
{
    return Unit::DimensionType<Unit::DimensionLess, Unit::_complex_unit_value_type>{std::polar(norm, phase.value)};
}

template <class dim_t>
inline auto proj(const Unit::DimensionType<dim_t, Unit::_complex_unit_value_type>& x)
{
    return std::proj(static_cast<Unit::_complex_unit_value_type>(x));
}

template <class dim_t>
inline auto sqrt(const Unit::DimensionType<dim_t, Unit::_complex_unit_value_type>& x)
{
    return Unit::DimensionType<decltype(dim_t{}.template root<2>()), Unit::_complex_unit_value_type>{
        std::sqrt(static_cast<Unit::_complex_unit_value_type>(x))};
}

#define DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(func)                                                                          \
    template <class T, ONLY_IF(std::is_same_v<T, Unit::DimensionType<Unit::DimensionLess, Unit::_complex_unit_value_type>>)> \
    inline auto func(const T& x)                                                                                             \
    {                                                                                                                        \
        return std::func(static_cast<Unit::_complex_unit_value_type>(x));                                                    \
    }

DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(acos);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(asin);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(atan);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(acosh);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(asinh);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(atanh);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(cos);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(cosh);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(exp);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(log);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(log10);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(sin);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(sinh);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(tan);
DECLARE_UNARY_CMATH_REDIRECT_FUNCTION(tanh);

#undef DECLARE_CMATH_REDIRECT_FUNCTION

}  // namespace std
