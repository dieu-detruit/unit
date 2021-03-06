#pragma once

#include <unit/impl/core.hpp>
#include <unit/impl/dimension.hpp>
#include <unit/impl/types.hpp>
#include <unit/impl/utility.hpp>

#include <cmath>
#include <complex>
#include <type_traits>

namespace Unit
{

using namespace std::literals::complex_literals;

namespace Impl
{
template <class dim_type>
struct polar_arg {
    using type = dim_type;
};
template <>
struct polar_arg<DimensionlessType> {
    using type = DimensionlessType::value_t;
};
template <class dim_type>
using polar_arg_t = typename polar_arg<dim_type>::type;

}  // namespace Impl


// Specialization of DimensionType for C++ standard complex values
template <class dim, typename value_type>
struct DimensionType<dim, std::complex<value_type>> {
private:
    using complex_type = std::complex<value_type>;
    using this_type = DimensionType<dim, std::complex<value_type>>;
    using real_type = DimensionType<dim, value_type>;
    using norm_type = DimensionType<decltype(dim{} * dim{}), value_type>;

public:
    using type = this_type;
    using dim_t = dim;
    using value_t = complex_type;
    using base_value_t = value_type;

    complex_type value;

    constexpr DimensionType() : value(value_type(0)) {}
    constexpr DimensionType(const this_type& lhs) : value(lhs.value) {}
    constexpr DimensionType(const this_type&& rhs) : value(rhs.value) {}
    constexpr DimensionType(const real_type& real, const real_type& imag) : value{complex_type(real.value, imag.value)} {}
    constexpr DimensionType(const real_type& real) : value{complex_type(real.value, 0.0)} {}
    constexpr DimensionType(const real_type&& real) : value{complex_type(real.value, 0.0)} {}
    explicit constexpr DimensionType(complex_type value) : value(value) {}
    explicit constexpr DimensionType(value_type real, value_type imag) : value{complex_type(real, imag)} {}

    // Cast Operators
    template <class T>
    explicit(std::is_floating_point_v<T> and !std::is_same_v<T, value_type>) constexpr operator std::complex<T>() const
    {
        return static_cast<std::complex<T>>(value);
    }

    constexpr operator real_type() { return real_type{value.real()}; }

    this_type& operator()() = delete;

    // Substitution Operators
#define DECLARE_SUBSTITUTION_OPERATOR(op)           \
    constexpr this_type& operator op(this_type arg) \
    {                                               \
        value op arg.value;                         \
        return *this;                               \
    }                                               \
    constexpr this_type& operator op(real_type arg) \
    {                                               \
        value op arg.value;                         \
        return *this;                               \
    }

    DECLARE_SUBSTITUTION_OPERATOR(=);   // this_type = this_type, this_type = real_type
    DECLARE_SUBSTITUTION_OPERATOR(+=);  // this_type += this_type, this_type += real_type
    DECLARE_SUBSTITUTION_OPERATOR(-=);  // this_type -= this_type, this_type -= real_type

#define DECLARE_SCALE_SUBSTITUTION_OPERATOR(op)                                                             \
    template <RightMultiplicableTo<value_type> T>                                                           \
    constexpr this_type& operator op(T scalar)                                                              \
    {                                                                                                       \
        value op scalar;                                                                                    \
        return *this;                                                                                       \
    }                                                                                                       \
    template <RightMultiplicableTo<value_type> T>                                                           \
    constexpr this_type& operator op(std::complex<T> scalar)                                                \
    {                                                                                                       \
        static_assert(std::is_convertible_v<value_type, T>, "You can only multiply floating point value."); \
        value op scalar;                                                                                    \
        return *this;                                                                                       \
    }                                                                                                       \
    constexpr this_type& operator op(DimensionType<DimensionlessDim, value_type> scalar)                    \
    {                                                                                                       \
        value op scalar.value;                                                                              \
        return *this;                                                                                       \
    }                                                                                                       \
    constexpr this_type& operator op(DimensionType<DimensionlessDim, complex_type> scalar)                  \
    {                                                                                                       \
        value op scalar.value;                                                                              \
        return *this;                                                                                       \
    }

    DECLARE_SCALE_SUBSTITUTION_OPERATOR(*=);  // this_type *= floating_point, this_type *= complex<floating>, this_type *= DimensionlessType
    DECLARE_SCALE_SUBSTITUTION_OPERATOR(/=);  // this_type /= floating_point, this_type /= real_type, this_type /= DimensionlessType

    // Unary Arithmetic Operators
    constexpr this_type operator+() const { return *this; }
    constexpr this_type operator-() const { return this_type{-value}; }

    template <int n>
    auto pow() const
    {
        return DimensionType<decltype(dim::template pow<n>()), value_type>{std::pow(value, n)};
    }
    template <int n, int d>
    auto pow() const
    {
        return DimensionType<decltype(decltype(dim::template pow<n>)::template root<d>), value_type>{std::pow(value, value_type(n) / d)};
    }
    template <int d>
    auto root() const
    {
        return DimensionType<decltype(dim::template root<d>()), value_type>{std::pow(value, value_type(1) / d)};
    }
    auto sqrt() const
    {
        return DimensionType<decltype(dim::template root<2>()), value_type>{std::sqrt(value)};
    }
    auto cbrt() const
    {
        return DimensionType<decltype(dim::template root<3>()), value_type>{std::cbrt(value)};
    }

    // Binary Bool Operators
#define DECLARE_BINARY_BOOL_OPERATOR(op)           \
    bool operator op(const this_type& right) const \
    {                                              \
        return value op right.value;               \
    }

    DECLARE_BINARY_BOOL_OPERATOR(==)
    DECLARE_BINARY_BOOL_OPERATOR(!=)
    DECLARE_BINARY_BOOL_OPERATOR(<)
    DECLARE_BINARY_BOOL_OPERATOR(<=)
    DECLARE_BINARY_BOOL_OPERATOR(>)
    DECLARE_BINARY_BOOL_OPERATOR(>=)

    bool operator==(const real_type& right) const { return value.real() == right.value and value.imag() == value_type(0); }
    bool operator!=(const real_type& right) const { return value.real() != right.value or value.imag() != value_type(0); }

    // Static Construc Function
    static constexpr auto polar(Impl::polar_arg_t<real_type> norm, Phase phase) { return this_type{norm * std::cos(phase.value), norm * std::sin(phase.value)}; }

    // Getter (Setter as a lvalue)
    constexpr auto real() const { return real_type{value.real()}; }
    constexpr auto imag() const { return real_type{value.imag()}; }

    // Setter
    void real(real_type real) { value.real(real.value); }
    void real(value_type real) { value.real(real); }

    void imag(real_type imag) { value.imag(imag.value); }
    void imag(value_type imag) { value.imag(imag); }

    // Basic functions for Complex quantity
    constexpr auto conj() const { return this_type{std::conj(value)}; }
    Phase arg() const { return Phase{std::arg(value)}; }
    constexpr auto norm() const { return norm_type{std::norm(value)}; }
    auto abs() const { return real_type{std::abs(value)}; }
};

#undef DECLARE_SUBSTITUTION_OPERATOR
#undef DECLARE_SCALE_SUBSTITUTION_OPERATOR
#undef DECLARE_SCALE_OPERATOR
#undef DECLARE_ADD_OPERATOR
#undef DECLARE_BINARY_BOOL_OPERATOR

}  // namespace Unit
