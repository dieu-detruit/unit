#pragma once

#include <type_traits>

#include <unit/impl/core.hpp>
#include <unit/impl/dimension.hpp>
#include <unit/impl/utility.hpp>

namespace Unit
{

#define DECLARE_HOMOGENIUS_ADD_OPERATOR(op)                                                                          \
    template <class dim, class left_value_type, class right_value_type>                                              \
    constexpr auto operator op(DimensionType<dim, left_value_type> left, DimensionType<dim, right_value_type> right) \
    {                                                                                                                \
        return DimensionType<dim, decltype(left_value_type {} op right_value_type{})>{left.value op right.value};    \
    }

DECLARE_HOMOGENIUS_ADD_OPERATOR(+);
DECLARE_HOMOGENIUS_ADD_OPERATOR(-);

#define DECLARE_DIMENSIONLESS_ADD_OPERATOR(op)                                                    \
    template <typename value_type, typename T,                                                    \
        ONLY_IF(not Impl::is_dim_type_v<T>)>                                                      \
    constexpr auto operator op(T left, DimensionType<DimensionLess, value_type> right)            \
    {                                                                                             \
        return DimensionType<DimensionLess, decltype(T {} op value_type{})>{left op right.value}; \
    }                                                                                             \
    template <typename T, typename value_type,                                                    \
        ONLY_IF(not Impl::is_dim_type_v<T>)>                                                      \
    constexpr auto operator op(DimensionType<DimensionLess, value_type> left, T right)            \
    {                                                                                             \
        return DimensionType<DimensionLess, decltype(value_type {} op T{})>{left op right.value}; \
    }

DECLARE_DIMENSIONLESS_ADD_OPERATOR(+);
DECLARE_DIMENSIONLESS_ADD_OPERATOR(-);

#define DECLARE_DIMENSIONAL_MULTIPLE_OPERATOR(op)                                                                                                \
    template <class left_dim, class right_dim, typename left_value_type, class right_value_type>                                                 \
    constexpr auto operator op(DimensionType<left_dim, left_value_type> left, DimensionType<right_dim, right_value_type> right)                  \
    {                                                                                                                                            \
        return DimensionType<decltype(left_dim {} op right_dim{}), decltype(left_value_type{} * right_value_type{})>{left.value op right.value}; \
    }

DECLARE_DIMENSIONAL_MULTIPLE_OPERATOR(*);
DECLARE_DIMENSIONAL_MULTIPLE_OPERATOR(/);

#define DECLARE_RIGHT_SCALE_OPERATOR(op)                                               \
    template <class dim, typename value_type, typename T,                              \
        ONLY_IF(not Impl::is_dim_type_v<T>)>                                           \
    constexpr auto operator op(DimensionType<dim, value_type> left, T scalar)          \
    {                                                                                  \
        return DimensionType<dim, decltype(value_type{} * T{})>{left.value op scalar}; \
    }

DECLARE_RIGHT_SCALE_OPERATOR(*);
DECLARE_RIGHT_SCALE_OPERATOR(/);

#define DECLARE_LEFT_SCALE_OPERATOR(op)                                                                                 \
    template <class dim, typename value_type, typename T,                                                               \
        ONLY_IF(not Impl::is_dim_type_v<T>)>                                                                            \
    constexpr auto operator op(T scalar, DimensionType<dim, value_type> right)                                          \
    {                                                                                                                   \
        return DimensionType<decltype(DimensionLess {} op dim{}), decltype(value_type{} * T{})>{scalar op right.value}; \
    }

DECLARE_LEFT_SCALE_OPERATOR(*);
DECLARE_LEFT_SCALE_OPERATOR(/);


#undef DECLARE_HOMOGENIUS_ADD_OPERATOR
#undef DECLARE_DIMENSIONLESS_ADD_OPERATOR
#undef DECLARE_DIMENSIONAL_MULTIPLE_OPERATOR
#undef DECLARE_RIGHT_SCALE_OPERATOR
#undef DECLARE_LEFT_SCALE_OPERATOR

}  // namespace Unit
