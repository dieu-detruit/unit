#pragma once

#include "unit/impl/core.hpp"
#include "unit/impl/dimension.hpp"
#include "unit/impl/operator.hpp"

namespace Unit
{

// Base Types
using Length = DimensionType<Dim<1, 0, 0, 0>, _unit_value_type>;
using Mass = DimensionType<Dim<0, 1, 0, 0>, _unit_value_type>;
using Time = DimensionType<Dim<0, 0, 1, 0>, _unit_value_type>;
using Current = DimensionType<Dim<0, 0, 0, 1>, _unit_value_type>;
using DimensionLessType = DimensionType<DimensionLess, _unit_value_type>;

// Derived Unit Types
using Vel = decltype(Length{} / Time{});
using Acc = decltype(Vel{} / Time{});
using Angle = DimensionLessType;
using Phase = DimensionLessType;
using AngularVel = decltype(Angle{} / Time{});
using AngularAcc = decltype(AngularVel{} / Time{});

using Force = decltype(Mass{} * Acc{});
using Energy = decltype(Force{} * Length{});
using Power = decltype(Energy{} / Time{});

using Area = decltype(Length{} * Length{});
using Frequency = decltype(DimensionLessType{} / Time{});

using Irradiance = decltype(Power{} / Area{});


}  // namespace Unit
