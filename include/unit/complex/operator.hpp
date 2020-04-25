#pragma once

#include "unit/complex/core.hpp"
#include "unit/impl/core.hpp"

#include <type_traits>

namespace Unit
{

template <class dim_type>
auto operator+(typename dim_type::value_t left, Complex<dim_type> right)  // value_t + Complex<dim_type> = Complex<dim_type>
{
    return Complex<dim_type>{left + right._real, right._imag};
}

template <class dim_type>
auto operator-(typename dim_type::value_t left, Complex<dim_type> right)  // value_t - Complex<dim_type> = Complex<dim_type>
{
    return Complex<dim_type>{left - right._real, -right._imag};
}

template <class dim_type, typename T, ONLY_IF(std::is_arithmetic_v<T>)>  // T * Complex<dim_type> = Complex<dim_type>
auto operator*(T left, Complex<dim_type> right)
{
    return Complex<dim_type>{left * right._real, left * right._imag};
}

template <class dim_type, typename T, ONLY_IF(std::is_arithmetic_v<T>)>  // T * Complex<dim_type> = Complex<1 / dim_type>
auto operator/(T left, Complex<dim_type> right)
{
    return Complex<decltype(DimensionLessType{} / dim_type{})>{left / right._real, left / right._imag};
}

}  // namespace Unit
