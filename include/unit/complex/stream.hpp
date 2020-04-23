#include "unit/complex/core.hpp"
#include "unit/impl/stream.hpp"

#include <iostream>

namespace Unit
{

template <class dim_type>
inline std::ostream& operator<<(std::ostream& os, const Complex<dim_type>& right)
{
    os << "(" << right._real.value << " + " << right._imag.value << " i)" << Impl::dimension_to_str(right._real);
    return os;
}

}  // namespace Unit
