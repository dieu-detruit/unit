#include <unit/complex/core.hpp>
#include <unit/impl/core.hpp>

#include <complex>

namespace Unit
{

// Access DimensionType<dim, std::complex<value>> as like Complex<Length>
template <class dim_type>
using Complex = DimensionType<typename dim_type::dim_t, std::complex<typename dim_type::value_t>>;

using _complex_unit_value_type = std::complex<_unit_value_type>;

}  // namespace Unit
