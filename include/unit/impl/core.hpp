#pragma once

#include "unit/impl/dimension.hpp"
#include "unit/impl/type_traits.hpp"

#include <iostream>
#include <type_traits>

namespace Unit
{

template <class dim, typename value_type>
struct ValueHolder {
    value_type value;
    constexpr ValueHolder(value_type value) : value(value) {}
};

template <typename value_type>
struct ValueHolder<DimensionLess, value_type> {
    value_type value;
    constexpr ValueHolder(value_type value) : value(value) {}
    constexpr operator value_type() { return value; }
};  // namespace Unit


template <class dim, typename value_type>
struct DimensionType : public ValueHolder<dim, value_type> {
private:
    using this_type = DimensionType<dim, value_type>;
    using holder_type = ValueHolder<dim, value_type>;

public:
    constexpr DimensionType() : holder_type(value_type(0)) {}
    constexpr DimensionType(const DimensionType& lhs) : holder_type(lhs.value) {}
    constexpr DimensionType(const DimensionType&& rhs) : holder_type(rhs.value) {}
    explicit constexpr DimensionType(value_type value) : holder_type(value) {}

    this_type& operator()() = delete;

    // Substitution Operators
    constexpr this_type& operator=(this_type arg)
    {
        this->value = arg.value;
        return *this;
    }
    constexpr this_type& operator+=(this_type right)
    {
        this->value += right.value;
        return *this;
    }
    constexpr this_type& operator/=(this_type right)
    {
        this->value += right.value;
        return *this;
    }
    template <class T, ONLY_IF(std::is_arithmetic_v<T>)>
    constexpr this_type& operator*=(T scalar)
    {
        static_assert(is_multiplicable_v<value_type, T>, "You can only multiply floating pointthis->value.");
        this->value *= scalar;
        return *this;
    }
    template <class T, ONLY_IF(std::is_arithmetic_v<T>)>
    constexpr this_type& operator/=(T scalar)
    {
        static_assert(is_multiplicable_v<value_type, T>, "You can only devide with floating pointthis->value.");
        this->value /= scalar;
        return *this;
    }

    // Unary Arithmetic Operators
    constexpr this_type operator+()
    {
        return *this;
    }
    constexpr this_type operator-()
    {
        return this_type{-this->value};
    }

    // Binary Arithmetic Operators
    template <typename T, ONLY_IF(std::is_arithmetic_v<T>)>
    constexpr this_type operator*(T scalar) const
    {
        static_assert(is_multiplicable_v<value_type, T>, "You can only multiply floating pointthis->value.");
        return this_type{this->value * scalar};
    }
    template <typename T, ONLY_IF(std::is_arithmetic_v<T>)>
    constexpr this_type operator/(T scalar) const
    {
        static_assert(is_multiplicable_v<value_type, T>, "You can only devide with floating pointthis->value.");
        return this_type{this->value / scalar};
    }
    template <class dim_>
    constexpr auto operator*(DimensionType<dim_, value_type> right) const
    {
        return DimensionType<decltype(dim{} * dim_{}), value_type>{this->value * right.value};
    }
    template <class dim_>
    constexpr auto operator/(DimensionType<dim_, value_type> right) const
    {
        return DimensionType<decltype(dim{} / dim_{}), value_type>{this->value / right.value};
    }

    constexpr this_type operator+(this_type right) const
    {
        return this_type{this->value + right.value};
    }
    constexpr this_type operator-(this_type right) const
    {
        return this_type{this->value - right.value};
    }

    // Binary Bool Operators

#define DECLARE_BINARY_BOOL_OPERATOR(op)     \
    bool operator op(const this_type& right) \
    {                                        \
        return this->value op right.value;   \
    }

    DECLARE_BINARY_BOOL_OPERATOR(==)
    DECLARE_BINARY_BOOL_OPERATOR(!=)
    DECLARE_BINARY_BOOL_OPERATOR(<)
    DECLARE_BINARY_BOOL_OPERATOR(<=)
    DECLARE_BINARY_BOOL_OPERATOR(>)
    DECLARE_BINARY_BOOL_OPERATOR(>=)
};

namespace Impl
{

template <typename T>
struct get_elements {
    using dim = std::nullptr_t;
    using value_type = T;
};

template <class _dim, typename T>
struct get_elements<DimensionType<_dim, T>> {
    using dim = _dim;
    using value_type = T;
};

template <class DT>
using get_dim_t = typename get_elements<DT>::dim;

template <class DT>
using get_value_type_t = typename get_elements<DT>::value_type;
}  // namespace Impl

#undef DECLARE_BINARY_BOOL_OPERATOR

}  // namespace Unit
