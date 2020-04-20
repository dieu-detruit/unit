#pragma once

#include "unit/impl/dimension.hpp"
#include "unit/impl/type_traits.hpp"

#include <iostream>
#include <type_traits>

namespace Unit
{

template <class dim, typename value_type>
struct DimensionType {
private:
    using this_type = DimensionType<dim, value_type>;

public:
    value_type value;

    constexpr DimensionType() : value(value_type(1)) {}
    constexpr DimensionType(const DimensionType& lhs) : value(lhs.value) {}
    constexpr DimensionType(const DimensionType&& rhs) : value(rhs.value) {}
    explicit constexpr DimensionType(value_type value) : value(value) {}

    this_type& operator()() = delete;

    // Substitution Operators
    constexpr this_type& operator=(this_type arg)
    {
        value = arg.value;
        return *this;
    }
    constexpr this_type& operator+=(this_type right)
    {
        value += right.value;
        return *this;
    }
    constexpr this_type& operator/=(this_type right)
    {
        value += right.value;
        return *this;
    }
    template <class T, ONLY_IF(std::is_arithmetic_v<T>)>
    constexpr this_type& operator*=(T scalar)
    {
        static_assert(is_multiplicable_v<value_type, T>, "You can only multiply floating point value.");
        value *= scalar;
        return *this;
    }
    template <class T, ONLY_IF(std::is_arithmetic_v<T>)>
    constexpr this_type& operator/=(T scalar)
    {
        static_assert(is_multiplicable_v<value_type, T>, "You can only devide with floating point value.");
        value /= scalar;
        return *this;
    }

    // Unary Arithmetic Operators
    constexpr this_type operator+()
    {
        return *this;
    }
    constexpr this_type operator-()
    {
        return this_type{-value};
    }

    // Binary Arithmetic Operators
    template <typename T, ONLY_IF(std::is_arithmetic_v<T>)>
    constexpr this_type operator*(T scalar) const
    {
        static_assert(is_multiplicable_v<value_type, T>, "You can only multiply floating point value.");
        return this_type{value * scalar};
    }
    template <typename T, ONLY_IF(std::is_arithmetic_v<T>)>
    constexpr this_type operator/(T scalar) const
    {
        static_assert(is_multiplicable_v<value_type, T>, "You can only devide with floating point value.");
        return this_type{value / scalar};
    }
    template <class dim_>
    constexpr auto operator*(DimensionType<dim_, value_type> right) const
    {
        return DimensionType<decltype(dim{} * dim_{}), value_type>{value * right.value};
    }
    template <class dim_>
    constexpr auto operator/(DimensionType<dim_, value_type> right) const
    {
        return DimensionType<decltype(dim{} / dim_{}), value_type>{value / right.value};
    }

    // Binary Bool Operators

#define DECLARE_BINARY_BOOL_OPERATOR(op)     \
    bool operator op(const this_type& right) \
    {                                        \
        return value op right.value;         \
    }

    DECLARE_BINARY_BOOL_OPERATOR(==)
    DECLARE_BINARY_BOOL_OPERATOR(!=)
    DECLARE_BINARY_BOOL_OPERATOR(<)
    DECLARE_BINARY_BOOL_OPERATOR(<=)
    DECLARE_BINARY_BOOL_OPERATOR(>)
    DECLARE_BINARY_BOOL_OPERATOR(>=)

    // Stream Operators
    //friend std::ostream& operator<<(std::ostream& os, const this_type& right);
};

}  // namespace Unit
