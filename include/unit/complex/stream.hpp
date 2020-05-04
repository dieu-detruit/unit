#include "unit/complex/core.hpp"
#include "unit/complex/types.hpp"
#include "unit/impl/stream.hpp"

#include <iostream>

namespace Unit
{

template <class dim, typename value_type>
inline std::ostream& operator<<(std::ostream& os, const DimensionType<dim, std::complex<value_type>>& right)
{
    os << right.value << Impl::dimension_to_str(DimensionType<dim, value_type>{});
    return os;
}

}  // namespace Unit
