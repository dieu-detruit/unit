#pragma once

#include "unit/impl/core.hpp"
#include "unit/impl/dimension.hpp"
#include "unit/impl/types.hpp"

#include <cmath>
#include <type_traits>

namespace Unit
{

namespace Impl
{
template <class dim_type>
struct polar_arg {
    using type = dim_type;
};
template <>
struct polar_arg<DimensionLessType> {
    using type = DimensionLessType::value_t;
};
template <class dim_type>
using polar_arg_t = typename polar_arg<dim_type>::type;


}  // namespace Impl

template <class dim_type = DimensionLessType>
struct Complex {
private:
    using this_type = Complex<dim_type>;
    using value_type = typename dim_type::value_t;

public:
    static_assert(Impl::is_dim_type<dim_type>::value, "You can only specify Unit type for template parameter.");

    dim_type _real;
    dim_type _imag;

    // Constructor
    constexpr Complex() : _real{}, _imag{} {}
    constexpr Complex(value_type real, value_type imag) : _real{real}, _imag{imag} {}
    constexpr Complex(value_type real) : _real{real}, _imag{} {}
    constexpr Complex(dim_type real, dim_type imag) : _real{real}, _imag{imag} {}
    constexpr Complex(dim_type real) : _real{real}, _imag{} {}
    constexpr Complex(const this_type& lhs) : _real{lhs._real}, _imag{lhs._imag} {}
    constexpr Complex(this_type&& rhs) : _real{rhs._real}, _imag{rhs._imag} {}

    // Static Maker Function
    static constexpr auto polar(Impl::polar_arg_t<dim_type> norm, Phase phase) { return this_type{norm * std::cos(phase), norm * std::sin(phase)}; }

    // Cast Operators
    constexpr operator dim_type() { return _real; }

    // Getter (Setter as a lvalue)
    dim_type& real() { return _real; }
    dim_type& imag() { return _imag; }

    // Setter
    void setReal(dim_type real) { _real = real; }
    void setImag(dim_type imag) { _imag = imag; }

    // Basic functions for Complex quantity
    constexpr this_type conj() { return {_real, -_imag}; }
    Phase arg() { return Phase{std::atan2(_imag.value, _real.value)}; }
    auto norm() { return dim_type{std::sqrt(_real.value * _real.value + _imag.value * _imag.value)}; }
    constexpr auto norm_square() { return _real * _real + _imag * _imag; }

    // Substitution operators
#define DECLARE_HOMOGENIOUS_SUBSTITUTION_OPERATOR(op) \
    constexpr this_type& operator op(this_type right) \
    {                                                 \
        _real op right._real;                         \
        _imag op right._imag;                         \
        return *this;                                 \
    }
    DECLARE_HOMOGENIOUS_SUBSTITUTION_OPERATOR(=);   // this_type = this_type
    DECLARE_HOMOGENIOUS_SUBSTITUTION_OPERATOR(+=);  // this_type += this_type
    DECLARE_HOMOGENIOUS_SUBSTITUTION_OPERATOR(-=);  // this_type -= this_type

#define DECLARE_SCALE_SUBSTITUTION_OPERATOR(op)       \
    constexpr this_type operator op(value_type right) \
    {                                                 \
        _real op right;                               \
        _imag op right;                               \
        return *this;                                 \
    }
    DECLARE_SCALE_SUBSTITUTION_OPERATOR(*=);  // this_type *= value_type
    DECLARE_SCALE_SUBSTITUTION_OPERATOR(/=);  // this_type /= value_type

    constexpr this_type operator*=(Complex<DimensionLessType> right)
    {
        auto _real_new = _real * right._real - _imag * right._imag;
        _imag = _real * right._imag + _imag * right._real;
        _real = _real_new;
        return *this;
    }
    constexpr this_type operator/=(Complex<DimensionLessType> right)
    {
        value_type temp = right._real.value * right._real.value + right._imag.value * right._imag.value;
        auto _real_new = (_real * right._real + _imag * right._imag) / temp;
        _imag = (_imag * right._real - _real * right._imag) / temp;
        _real = _real_new;
        return *this;
    }

    // Unary arithmetic operators
    constexpr this_type operator+() { return *this; }                      // +this_type
    constexpr this_type operator-() { return this_type{-_real, -_imag}; }  // -this_type

    // Binary arithmetic operators
    constexpr this_type operator+(this_type right) { return this_type{_real + right._real, _imag + right._imag}; }  // this_type + this_type
    constexpr this_type operator-(this_type right) { return this_type{_real - right._real, _imag - right._imag}; }  // this_type - this_type

    constexpr this_type operator+(dim_type right) { return this_type{_real + right, _imag}; }  // this_type + dim_type
    constexpr this_type operator-(dim_type right) { return this_type{_real - right, _imag}; }  // this_type - dim_type

    constexpr this_type operator*(value_type right) { return this_type{_real * right, _imag * right}; }  // this_type * value_type
    constexpr this_type operator/(value_type right) { return this_type{_real / right, _imag / right}; }  // this_type / value_type

    constexpr this_type operator*(Complex<DimensionLessType> right)  // this_type * Complex
    {
        return this_type{
            _real * right._real - _imag * right._imag,
            _real * right._imag + _imag * right._real};
    }
    constexpr this_type operator/(Complex<DimensionLessType> right)  // this_type / Complex
    {
        return this_type{
                   _real * right._real + _imag * right._imag,
                   _imag * right._real - _real * right._imag}
               / (right._real.value * right._real.value + right._imag.value * right._imag.value);
    }
    template <class arg_dim_type>
    constexpr auto operator*(arg_dim_type right)
    {
        return Complex<decltype(dim_type{} * arg_dim_type{})>{_real * right, _imag * right};
    }

    // Bool operators
    bool operator==(const this_type& right)  // this_type == this_type
    {
        return (_real == right._real) && (_imag == right._imag);
    }
    bool operator!=(const this_type& right)  // this_type != this_type
    {
        return (_real != right._real) || (_imag != right._imag);
    }
};  // namespace Impltemplate<classdim_type=DimensionLessType>structComplex

template <class dim_type>
auto polar(dim_type norm, Phase phase)
{
    return Complex<dim_type>{norm * std::cos(phase), norm * std::sin(phase)};
}

auto polar(_unit_value_type norm, Phase phase)
{
    return Complex<>{norm * std::cos(phase), norm * std::sin(phase)};
}

#undef DECLARE_HOMOGENIUS_SUBSTITUTION_OPERATOR
#undef DECLARE_SCALE_SUBSTITUTION_OPERATOR

}  // namespace Unit
