#pragma once

#include "unit/impl/dimension.hpp"
#include "unit/impl/utility.hpp"

#include <cmath>
#include <complex>
#include <type_traits>

namespace Unit
{

template <class dim, typename value_type>
struct DimensionType {
private:
    using this_type = DimensionType<dim, value_type>;
    using complex_dim_type = DimensionType<dim, std::complex<value_type>>;

public:
    using type = this_type;
    using dim_t = dim;
    using value_t = value_type;

    value_type value;

    constexpr DimensionType() : value(static_cast<value_type>(0)) {}
    constexpr DimensionType(const DimensionType& lhs) : value(lhs.value) {}
    constexpr DimensionType(const DimensionType&& rhs) : value(rhs.value) {}
    explicit constexpr DimensionType(value_type value) : value(value) {}

    template <class T, ONLY_IF(std::is_convertible_v<T, value_type>)>
    constexpr operator T() const
    {
        static_assert(std::is_same_v<dim, DimensionLess>, "Only dimension-less type can be casted to value type.");
        return static_cast<T>(value);
    }

// Substitution Operators
#define DECLARE_SUBSTITUTION_OPERATOR(op)           \
    constexpr this_type& operator op(this_type arg) \
    {                                               \
        value op arg.value;                         \
        return *this;                               \
    }

    DECLARE_SUBSTITUTION_OPERATOR(=);   // this_type = this_type
    DECLARE_SUBSTITUTION_OPERATOR(+=);  // this_type += this_type
    DECLARE_SUBSTITUTION_OPERATOR(-=);  // this_type -= this_type

#define DECLARE_SCALE_SUBSTITUTION_OPERATOR(op)                                                             \
    template <class T, ONLY_IF(std::is_arithmetic_v<T>)>                                                    \
    constexpr this_type& operator op(T scalar)                                                              \
    {                                                                                                       \
        static_assert(std::is_convertible_v<value_type, T>, "You can only multiply floating point value."); \
        value op scalar;                                                                                    \
        return *this;                                                                                       \
    }                                                                                                       \
    constexpr this_type& operator op(DimensionType<DimensionLess, value_type> scalar)                       \
    {                                                                                                       \
        value op scalar.value;                                                                              \
        return *this;                                                                                       \
    }

    DECLARE_SCALE_SUBSTITUTION_OPERATOR(*=);
    DECLARE_SCALE_SUBSTITUTION_OPERATOR(/=);

    // Unary Arithmetic Operators
    constexpr this_type operator+() const { return *this; }
    constexpr this_type operator-() const { return this_type{-value}; }

// Binary Arithmetic Operators
#define DECLARE_SCALE_OPERATOR(op)                                                                                               \
    template <typename T, ONLY_IF(std::is_arithmetic_v<T>)>                                                                      \
    constexpr this_type operator op(T scalar) const                                                                              \
    {                                                                                                                            \
        static_assert(std::is_convertible_v<value_type, T>, "You can only multiply value of a type convertible to value_type."); \
        return this_type{value op scalar};                                                                                       \
    }                                                                                                                            \
    template <class dim_>                                                                                                        \
    constexpr auto operator op(DimensionType<dim_, value_type> right) const                                                      \
    {                                                                                                                            \
        return DimensionType<decltype(dim {} op dim_{}), value_type>{value op right.value};                                      \
    }                                                                                                                            \
    template <class dim_>                                                                                                        \
    constexpr auto operator op(DimensionType<dim_, std::complex<value_type>> right) const                                        \
    {                                                                                                                            \
        return DimensionType<decltype(dim {} op dim_{}), std::complex<value_type>>{value op right.value};                        \
    }


    DECLARE_SCALE_OPERATOR(*);
    DECLARE_SCALE_OPERATOR(/);

#define DECLARE_ADD_OPERATOR(op)                                         \
    constexpr this_type operator op(this_type right) const               \
    {                                                                    \
        return this_type{value op right.value};                          \
    }                                                                    \
    constexpr complex_dim_type operator op(complex_dim_type right) const \
    {                                                                    \
        return complex_dim_type{value op right.value};                   \
    }

    DECLARE_ADD_OPERATOR(+);  // this_type + this_type = this_type, this_type + complex_dim_type = complex_dim_type
    DECLARE_ADD_OPERATOR(-);  // this_type - this_type = this_type, this_type - complex_dim_type = complex_dim_type

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
        return DimensionType<decltype(dim::template root<d>()), value_type>{std::pow(value, static_cast<value_type>(1) / d)};
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

    bool operator==(const complex_dim_type& right) const { return value == right.value.real() and right.value.real() == static_cast<value_type>(0); }
    bool operator!=(const complex_dim_type& right) const { return value != right.value.real() or right.value.real() != static_cast<value_type>(0); }
};

namespace Impl
{

template <class T>
struct is_dim_type {
    static constexpr bool value = false;
};

template <class dim, typename value_type>
struct is_dim_type<DimensionType<dim, value_type>> {
    static constexpr bool value = true;
};

#undef DECLARE_SUBSTITUTION_OPERATOR
#undef DECLARE_SCALE_SUBSTITUTION_OPERATOR
#undef DECLARE_SCALE_OPERATOR
#undef DECLARE_ADD_OPERATOR
#undef DECLARE_BINARY_BOOL_OPERATOR

}  // namespace Impl

}  // namespace Unit
