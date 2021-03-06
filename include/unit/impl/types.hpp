#pragma once

#include <unit/impl/core.hpp>
#include <unit/impl/dimension.hpp>
#include <unit/impl/operator.hpp>

namespace Unit
{

inline constexpr long _idx = 1;

// SI Base Unit Types
using Length = /*----------- L */ DimensionType<Dim<_idx, 1, 0, 0, 0, 0, 0, 0>>;
using Mass = /*------------- M */ DimensionType<Dim<_idx, 0, 1, 0, 0, 0, 0, 0>>;
using Time = /*------------- T */ DimensionType<Dim<_idx, 0, 0, 1, 0, 0, 0, 0>>;
using Temperature = /*-- Theta */ DimensionType<Dim<_idx, 0, 0, 0, 1, 0, 0, 0>>;
using Amount = /*----------- N */ DimensionType<Dim<_idx, 0, 0, 0, 0, 1, 0, 0>>;
using Current = /*---------- I */ DimensionType<Dim<_idx, 0, 0, 0, 0, 0, 1, 0>>;
using LuminousIntensity = /* J */ DimensionType<Dim<_idx, 0, 0, 0, 0, 0, 0, 1>>;
using DimensionlessType = /* 1 */ DimensionType<DimensionlessDim>;

// Derived Unit Types
using Velocity = decltype(Length{} / Time{});
using Acceleration = decltype(Velocity{} / Time{});
using Angle = DimensionlessType;
using AngularVel = decltype(Angle{} / Time{});
using AngularAcc = decltype(AngularVel{} / Time{});

using Force = decltype(Mass{} * Acceleration{});
using Energy = decltype(Force{} * Length{});
using Power = decltype(Energy{} / Time{});

using Area = decltype(Length{} * Length{});

using Phase = DimensionlessType;
using Frequency = decltype(DimensionlessType{} / Time{});

using ElectricCharge = decltype(Current{} * Time{});
using Voltage = decltype(Energy{} / ElectricCharge{});
using Resistance = decltype(Voltage{} / Current{});
using ElectrostaticCapacity = decltype(ElectricCharge{} / Voltage{});
using Permittivity = decltype(ElectrostaticCapacity{} / Length{});
using Conductance = decltype(DimensionlessType{} / Resistance{});
using Admittance = Conductance;
using Susceptance = Conductance;
using MagneticFlux = decltype(Voltage{} * Time{});
using MagneticFluxDensity = decltype(MagneticFlux{} * Area{});
using Inductance = decltype(MagneticFlux{} / Current{});

using SolidAngle = DimensionlessType;
using LuminousFlux = decltype(LuminousIntensity{} * SolidAngle{});
using LuminousEnergy = decltype(LuminousFlux{} * Time{});
using Luminance = decltype(LuminousIntensity{} / Area{});
using Illuminance = decltype(LuminousFlux{} / Area{});
using LuminousRadiance = decltype(LuminousFlux{} / Area{});
using LuminousityFactor = DimensionlessType;
using LuminousityEfficacy = decltype(LuminousFlux{} / Power{});
using Irradiance = decltype(Power{} / Area{});

}  // namespace Unit
