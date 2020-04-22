#pragma once

#include "unit/impl/constants.hpp"
#include "unit/impl/operator.hpp"
#include "unit/impl/types.hpp"

namespace Unit
{

constexpr auto _cast(long double c) { return static_cast<_unit_value_type>(c); }

#define DECLARE_CONST_BASE(dim, name) inline constexpr dim name{_cast(1.0L)};
#define DECLARE_CONST_IMPL(dim, prefix, name, mag) \
    inline constexpr dim prefix##name = static_cast<_unit_value_type>((mag)) * name;
#define DECLARE_CONST_FROM_VALUE(dim, name, value) inline constexpr dim name{value};

#define DECLARE_CONST(dim, name)                   \
    DECLARE_CONST_BASE(dim, name)                  \
    DECLARE_CONST_IMPL(dim, femto, name, 1.0e-15L) \
    DECLARE_CONST_IMPL(dim, pico, name, 1.0e-12L)  \
    DECLARE_CONST_IMPL(dim, nano, name, 1.0e-9L)   \
    DECLARE_CONST_IMPL(dim, micro, name, 1.0e-6L)  \
    DECLARE_CONST_IMPL(dim, milli, name, 1.0e-3L)  \
    DECLARE_CONST_IMPL(dim, kilo, name, 1.0e+3L)   \
    DECLARE_CONST_IMPL(dim, mega, name, 1.0e+6L)   \
    DECLARE_CONST_IMPL(dim, giga, name, 1.0e+9L)   \
    DECLARE_CONST_IMPL(dim, tera, name, 1.0e+12L)  \
    DECLARE_CONST_IMPL(dim, peta, name, 1.0e+15L)

// SI Base Units
DECLARE_CONST(Length, meter)
DECLARE_CONST(Mass, gram)
DECLARE_CONST(Time, second)
DECLARE_CONST(Temperature, kelvin)
DECLARE_CONST(Amount, mole)
DECLARE_CONST(Current, ampere)
DECLARE_CONST(LuminousIntensity, candera)

// Derived Units
DECLARE_CONST(Angle, radian)
DECLARE_CONST(SolidAngle, steradian)
DECLARE_CONST(Force, newton)
DECLARE_CONST(Power, watt)
DECLARE_CONST(Energy, joule)
DECLARE_CONST(Frequency, hertz)

DECLARE_CONST(ElectricCharge, coulomb)
DECLARE_CONST(Voltage, volt)
DECLARE_CONST(Resistance, ohm)
DECLARE_CONST(ElectrostaticCapacity, farad)
DECLARE_CONST(Conductance, siemens)
DECLARE_CONST(MagneticFlux, weber)
DECLARE_CONST(MagneticFluxDensity, tesla)
DECLARE_CONST(Inductance, henry)

DECLARE_CONST(LuminousFlux, lumen)

// Non SI Units
DECLARE_CONST_FROM_VALUE(Time, minute, _cast(60.0L) * second)
DECLARE_CONST_FROM_VALUE(Time, hour, _cast(60.0L) * minute)
DECLARE_CONST_FROM_VALUE(Time, day, _cast(24.0L) * hour)
DECLARE_CONST_FROM_VALUE(Length, astronomical_unit, _cast(149597870700.0L) * meter)
DECLARE_CONST_FROM_VALUE(Energy, electron_volt, Voltage{_cast(1.0L)} * Constant::elementary_charge)
DECLARE_CONST_FROM_VALUE(Energy, kiloelectron_volt, _cast(1.0e+3L) * electron_volt)
DECLARE_CONST_FROM_VALUE(Energy, megaelectron_volt, _cast(1.0e+6L) * electron_volt)
DECLARE_CONST_FROM_VALUE(Energy, gigaelectron_volt, _cast(1.0e+9L) * electron_volt)

}  // namespace Unit
