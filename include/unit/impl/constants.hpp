#pragma once

#include "unit/impl/base_quantity.hpp"
#include "unit/impl/types.hpp"

namespace Unit::Constant
{

constexpr auto _cast(long double c) { return static_cast<_unit_value_type>(c); }

// Constants SI Units Definition depends on
//
inline constexpr Frequency caesium133_frequency{_cast(9192631770.0L)};
inline constexpr Velocity speed_of_light{_cast(299792458.0L)};
inline constexpr decltype(Energy{} * Time{}) planck_constant{_cast(6.62607015e-34L)};
inline constexpr ElectricCharge elementary_charge{_cast(1.602176634e-19L)};
inline constexpr decltype(Energy{} / Temperature{}) boltzmann_constant{_cast(1.380649e-23L)};
inline constexpr decltype(DimensionLessType{} / Amount{}) avogadro_constant{_cast(6.02214076e+23L)};
inline constexpr LuminousityEfficacy max_luminous_efficacy{_cast(683.0L)};

inline constexpr auto pi = _cast(3.1415926535897932384626L);


}  // namespace Unit::Constant
