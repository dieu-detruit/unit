#pragma once

#include <string>

#include <unit/impl/base_quantity.hpp>
#include <unit/impl/constants.hpp>
#include <unit/impl/core.hpp>
#include <unit/impl/types.hpp>

namespace Unit
{

namespace Impl
{

template <class dim_type>
struct has_literal {
    static constexpr bool value = false;
};
template <class dim_type>
struct literal_of {
    static constexpr std::nullptr_t get = nullptr;
};

}  // namespace Impl


#define DECLARE_LITERAL_IMPL_LI(unit_type, constant, literal)          \
    inline constexpr unit_type operator""_##literal(long double value) \
    {                                                                  \
        return static_cast<typename unit_type::value_t>(value)         \
               * constant;                                             \
    }

#define DECLARE_LITERAL_IMPL_SQ(unit_type, constant, literal)             \
    inline constexpr unit_type operator""_##literal##2(long double value) \
    {                                                                     \
        return static_cast<typename unit_type::value_t>(value)            \
               * (constant * constant);                                   \
    }

#define DECLARE_LITERAL_SET_IMPL(DIM, unit_type, constant, literal, literal_str) \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, femto##constant, f##literal);          \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, pico##constant, p##literal);           \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, nano##constant, n##literal);           \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, micro##constant, u##literal);          \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, milli##constant, m##literal);          \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, constant, literal);                    \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, kilo##constant, k##literal);           \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, mega##constant, M##literal);           \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, giga##constant, G##literal);           \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, tera##constant, T##literal);           \
    DECLARE_LITERAL_IMPL_##DIM(unit_type, peta##constant, P##literal);           \
    namespace Impl                                                               \
    {                                                                            \
    template <>                                                                  \
    struct has_literal<unit_type> {                                              \
        static constexpr bool value = true;                                      \
    };                                                                           \
    template <>                                                                  \
    struct literal_of<unit_type> {                                               \
        static constexpr auto get = []() -> std::string {                        \
            return literal_str;                                                  \
        };                                                                       \
    };                                                                           \
    }

#define DECLARE_LITERAL_SET(unit_type, constant, literal) \
    DECLARE_LITERAL_SET_IMPL(LI, unit_type, constant, literal, #literal)

#define DECLARE_LITERAL_SET_SQ(unit_type, constant, literal) \
    DECLARE_LITERAL_SET_IMPL(SQ, unit_type, constant, literal, #literal "^2")

// SI Base Units
DECLARE_LITERAL_SET(Length, meter, m)
DECLARE_LITERAL_SET(Mass, gram, g)
DECLARE_LITERAL_SET(Time, second, s)
DECLARE_LITERAL_SET(Temperature, kelvin, K)
DECLARE_LITERAL_SET(Amount, mole, mol)
DECLARE_LITERAL_SET(Current, ampere, A)
DECLARE_LITERAL_SET(LuminousIntensity, candera, cd)

// Derived SI Units
DECLARE_LITERAL_IMPL_LI(Angle, radian, rad)
DECLARE_LITERAL_IMPL_LI(Angle, milliradian, mrad)
DECLARE_LITERAL_IMPL_LI(Angle, microradian, urad)
DECLARE_LITERAL_IMPL_LI(Angle, nanoradian, nrad)
DECLARE_LITERAL_SET(Force, newton, N)
DECLARE_LITERAL_SET(Power, watt, W)
DECLARE_LITERAL_SET(Energy, joule, J)
DECLARE_LITERAL_SET(Frequency, hertz, Hz)

DECLARE_LITERAL_SET(ElectricCharge, coulomb, C)
DECLARE_LITERAL_SET(Voltage, volt, V)
DECLARE_LITERAL_SET(Resistance, ohm, ohm)
DECLARE_LITERAL_SET(ElectrostaticCapacity, farad, F)
DECLARE_LITERAL_SET(Conductance, siemens, S)
DECLARE_LITERAL_SET(MagneticFlux, weber, Wb)
DECLARE_LITERAL_SET(MagneticFluxDensity, tesla, T)
DECLARE_LITERAL_SET(Inductance, henry, H)

DECLARE_LITERAL_IMPL_LI(LuminousFlux, lumen, lm)

// Additional SI Units
DECLARE_LITERAL_SET_SQ(Area, meter, m)

// Non SI Units
DECLARE_LITERAL_IMPL_LI(Time, minute, min)
DECLARE_LITERAL_IMPL_LI(Time, hour, h)
DECLARE_LITERAL_IMPL_LI(Time, day, d)
DECLARE_LITERAL_IMPL_LI(Length, astronomical_unit, au)
DECLARE_LITERAL_IMPL_LI(Energy, electron_volt, eV)
DECLARE_LITERAL_IMPL_LI(Energy, kiloelectron_volt, keV)
DECLARE_LITERAL_IMPL_LI(Energy, megaelectron_volt, MeV)
DECLARE_LITERAL_IMPL_LI(Energy, gigaelectron_volt, GeV)


#undef DECLARE_LITERAL_IMPL_LI
#undef DECLARE_LITERAL_IMPL_SQ
#undef DECLARE_LITERAL_SET_IMPL
#undef DECLARE_LITERAL_SET
#undef DECLARE_LITERAL_SET_SQ

}  // namespace Unit
