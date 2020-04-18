#pragma once

#include "unit/impl/operator.hpp"
#include "unit/impl/quantity.hpp"

namespace Unit
{

namespace SI
{


#define DECLARE_CONST_BASE(dim, name) inline constexpr dim name{};
#define DECLARE_CONST_IMPL(dim, prefix, name, mag) \
    inline constexpr dim prefix##name = mag * name;

#define DECLARE_CONST(dim, name)                                                 \
    DECLARE_CONST_BASE(dim, name)                                                \
    DECLARE_CONST_IMPL(dim, micro, name, static_cast<_unit_value_type>(1.0e-6L)) \
    DECLARE_CONST_IMPL(dim, milli, name, static_cast<_unit_value_type>(1.0e-3L)) \
    DECLARE_CONST_IMPL(dim, kilo, name, static_cast<_unit_value_type>(1.0e+3L))  \
    DECLARE_CONST_IMPL(dim, mega, name, static_cast<_unit_value_type>(1.0e+6L))

// Unit Constants
DECLARE_CONST(Length, meter)
DECLARE_CONST(Mass, gram)
DECLARE_CONST(Time, second)
DECLARE_CONST(Current, ampere)

DECLARE_CONST(Angle, radian)
DECLARE_CONST(Force, newton)
DECLARE_CONST(Power, watt)
DECLARE_CONST(Energy, joule)
DECLARE_CONST(Frequency, hertz)

}  // namespace SI

}  // namespace Unit
