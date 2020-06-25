#pragma once

#include <unit/impl/dimension.hpp>
#include <unit/impl/utility.hpp>

#include <cmath>
#include <complex>
#include <type_traits>

namespace Unit
{

template <class T, class U>
concept RightMultiplicableTo = requires(T& x, U& y)
{
    {
        x* y
    }
    ->std::convertible_to<U>;
};

template <class T>
concept non_referential = not std::is_reference_v<T>;

template <class T>
concept referential = std::is_reference_v<T>;

template <class T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

template <class T, class U>
concept other_floating_point = std::same_as<T, U>and std::floating_point<T>;

template <class T>
concept non_floating_point = not std::floating_point<T>;

template <Dimensional dim, non_referential value_type = _unit_value_type>
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

    // allow only value_type floating-point value to cast implicitly to avoid ambiguous function call of std
    //template <typename T>
    //explicit(not std::is_same_v<T, value_type>) constexpr operator T() const requires Dimensionless<dim>
    //{
    //return static_cast<T>(value);
    //}

    template <non_floating_point T>
    explicit constexpr operator T() requires Dimensionless<dim>
    {
        return static_cast<T>(value);
    }
    template <other_floating_point<value_type> T>
    operator T() = delete;

    constexpr operator value_type&() requires Dimensionless<dim>
    {
        return value;
    }
    constexpr operator const value_type&() const requires Dimensionless<dim>
    {
        return value;
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


#define DECLARE_SCALE_SUBSTITUTION_OPERATOR(op)                                          \
    template <RightMultiplicableTo<value_type> T>                                        \
    constexpr this_type& operator op(T scalar)                                           \
    {                                                                                    \
        value op scalar;                                                                 \
        return *this;                                                                    \
    }                                                                                    \
    constexpr this_type& operator op(DimensionType<DimensionlessDim, value_type> scalar) \
    {                                                                                    \
        value op scalar.value;                                                           \
        return *this;                                                                    \
    }

    DECLARE_SCALE_SUBSTITUTION_OPERATOR(*=);
    DECLARE_SCALE_SUBSTITUTION_OPERATOR(/=);

    // Unary Arithmetic Operators
    constexpr this_type operator+() const { return *this; }
    constexpr this_type operator-() const { return this_type{-value}; }

    // Binary Arithmetic Operators
    template <long n>
    auto pow() const
    {
        return DimensionType<decltype(dim::template pow<n>()), value_type>{std::pow(value, n)};
    }
    template <long n, long d>
    auto pow() const
    {
        return DimensionType<decltype(decltype(dim::template pow<n>)::template root<d>), value_type>{std::pow(value, value_type(n) / d)};
    }
    template <long d>
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

    bool
    operator==(const complex_dim_type& right) const
    {
        return value == right.value.real() and right.value.real() == static_cast<value_type>(0);
    }
    bool
    operator!=(const complex_dim_type& right) const { return value != right.value.real() or right.value.real() != static_cast<value_type>(0); }
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

template <class T>
inline constexpr bool is_dim_type_v = is_dim_type<T>::value;

#undef DECLARE_SUBSTITUTION_OPERATOR
#undef DECLARE_SCALE_SUBSTITUTION_OPERATOR
#undef DECLARE_SCALE_OPERATOR
#undef DECLARE_ADD_OPERATOR
#undef DECLARE_BINARY_BOOL_OPERATOR

}  // namespace Impl

}  // namespace Unit
