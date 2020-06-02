#include "unit/complex/core.hpp"
#include "unit/complex/types.hpp"
#include "unit/impl/types.hpp"
#include <complex>

namespace Unit
{
}

namespace std
{

template <class dim_t>
auto real(Unit::DimensionType<dim_t, Unit::_complex_unit_value_type> c)
{
    return c.real();
}
template <class dim_t>
auto imag(Unit::DimensionType<dim_t, Unit::_complex_unit_value_type> c)
{
    return c.imag();
}
template <class dim_t>
auto conj(Unit::DimensionType<dim_t, Unit::_complex_unit_value_type> c)
{
    return c.conj();
}
template <class dim_t>
auto arg(Unit::DimensionType<dim_t, Unit::_complex_unit_value_type> c)
{
    return c.arg();
}
template <class dim_t>
auto norm(Unit::DimensionType<dim_t, Unit::_complex_unit_value_type> c)
{
    return c.norm();
}
template <class dim_t>
auto abs(Unit::DimensionType<dim_t, Unit::_complex_unit_value_type> c)
{
    return c.abs();
}

template <class dim_type>
auto polar(dim_type norm, Unit::Phase phase)
{
    return Unit::DimensionType<typename dim_type::dim_t, std::complex<typename dim_type::value_t>>{std::polar(norm.value, phase.value)};
}

auto polar(Unit::_unit_value_type norm, Unit::Phase phase)
{
    return Unit::DimensionType<Unit::DimensionLess, std::complex<Unit::_unit_value_type>>{std::polar(norm, phase.value)};
}


}  // namespace std
