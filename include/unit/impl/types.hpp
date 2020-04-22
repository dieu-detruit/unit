#pragma once

#include "unit/impl/core.hpp"
#include "unit/impl/dimension.hpp"
#include "unit/impl/operator.hpp"

namespace Unit
{

// SI Base Unit Types
using Length = /*----------- L */ DimensionType<Dim<1, 0, 0, 0, 0, 0, 0>, _unit_value_type>;
using Mass = /*------------- M */ DimensionType<Dim<0, 1, 0, 0, 0, 0, 0>, _unit_value_type>;
using Time = /*------------- T */ DimensionType<Dim<0, 0, 1, 0, 0, 0, 0>, _unit_value_type>;
using Temperature = /*-- Theta */ DimensionType<Dim<0, 0, 0, 1, 0, 0, 0>, _unit_value_type>;
using Amount = /*----------- N */ DimensionType<Dim<0, 0, 0, 0, 1, 0, 0>, _unit_value_type>;
using Current = /*---------- I */ DimensionType<Dim<0, 0, 0, 0, 0, 1, 0>, _unit_value_type>;
using LuminousIntensity = /* J */ DimensionType<Dim<0, 0, 0, 0, 0, 0, 1>, _unit_value_type>;
using DimensionLessType = /* 1 */ DimensionType<DimensionLess, _unit_value_type>;

// Derived Unit Types
using Velocity = decltype(Length{} / Time{});
using Acceleration = decltype(Velocity{} / Time{});
using Angle = DimensionLessType;
using AngularVel = decltype(Angle{} / Time{});
using AngularAcc = decltype(AngularVel{} / Time{});

using Force = decltype(Mass{} * Acceleration{});
using Energy = decltype(Force{} * Length{});
using Power = decltype(Energy{} / Time{});

using Area = decltype(Length{} * Length{});

using Phase = DimensionLessType;
using Frequency = decltype(DimensionLessType{} / Time{});

using ElectricCharge = decltype(Current{} * Time{});
using Voltage = decltype(Energy{} / ElectricCharge{});
using Resistance = decltype(Voltage{} / Current{});
using ElectrostaticCapacity = decltype(ElectricCharge{} / Voltage{});
using Permittivity = decltype(ElectrostaticCapacity{} / Length{});
using Conductance = decltype(DimensionLessType{} / Resistance{});
using Admittance = Conductance;
using Susceptance = Conductance;
using MagneticFlux = decltype(Voltage{} * Time{});
using MagneticFluxDensity = decltype(MagneticFlux{} * Area{});
using Inductance = decltype(MagneticFlux{} / Current{});

using SolidAngle = DimensionLessType;
using LuminousFlux = decltype(LuminousIntensity{} * SolidAngle{});
using LuminousEnergy = decltype(LuminousFlux{} * Time{});
using Luminance = decltype(LuminousIntensity{} / Area{});
using Illuminance = decltype(LuminousFlux{} / Area{});
using LuminousRadiance = decltype(LuminousFlux{} / Area{});
using LuminousityFactor = DimensionLessType;
using LuminousityEfficacy = decltype(LuminousFlux{} / Power{});
using Irradiance = decltype(Power{} / Area{});

}  // namespace Unit
