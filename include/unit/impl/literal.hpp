#pragma once

#include "unit/impl/core.hpp"
#include "unit/impl/literal.hpp"
#include "unit/impl/quantity.hpp"
#include "unit/impl/si.hpp"

namespace Unit
{

template <typename T>
struct get_value_type {
    using type = T;
};

template <class dim, typename T>
struct get_value_type<DimensionType<dim, T>> {
    using type = T;
};

#define DECLARE_LITERAL_IMPL(unit_type, constant, literal)                  \
    inline constexpr unit_type operator""_##literal(long double value)      \
    {                                                                       \
        return static_cast<typename get_value_type<unit_type>::type>(value) \
               * (SI::constant);                                            \
    }

#define DECLARE_LITERAL_IMPL_SQ(unit_type, constant, literal)               \
    inline constexpr unit_type operator""_##literal##2(long double value)   \
    {                                                                       \
        return static_cast<typename get_value_type<unit_type>::type>(value) \
               * (SI::constant * SI::constant);                             \
    }

#define DECLARE_LITERAL(unit_type, constant, literal)            \
    DECLARE_LITERAL_IMPL(unit_type, micro##constant, u##literal) \
    DECLARE_LITERAL_IMPL(unit_type, milli##constant, m##literal) \
    DECLARE_LITERAL_IMPL(unit_type, constant, literal)           \
    DECLARE_LITERAL_IMPL(unit_type, kilo##constant, k##literal)  \
    DECLARE_LITERAL_IMPL(unit_type, mega##constant, M##literal)

#define DECLARE_LITERAL_SQ(unit_type, constant, literal)            \
    DECLARE_LITERAL_IMPL_SQ(unit_type, micro##constant, u##literal) \
    DECLARE_LITERAL_IMPL_SQ(unit_type, milli##constant, m##literal) \
    DECLARE_LITERAL_IMPL_SQ(unit_type, constant, literal)           \
    DECLARE_LITERAL_IMPL_SQ(unit_type, kilo##constant, k##literal)  \
    DECLARE_LITERAL_IMPL_SQ(unit_type, mega##constant, M##literal)


DECLARE_LITERAL(Length, meter, m)
DECLARE_LITERAL(Mass, gram, g)
DECLARE_LITERAL(Time, second, s)
DECLARE_LITERAL(Current, ampere, A)

DECLARE_LITERAL(Angle, radian, rad)
DECLARE_LITERAL(Force, newton, N)
DECLARE_LITERAL(Power, watt, W)
DECLARE_LITERAL(Energy, joule, J)
DECLARE_LITERAL(Frequency, hertz, Hz)

DECLARE_LITERAL_SQ(Area, meter, m)


}  // namespace Unit
