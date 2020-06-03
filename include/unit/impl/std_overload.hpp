#include "unit/impl/core.hpp"

namespace std
{
template <class dim_t>
auto sqrt(Unit::DimensionType<dim_t, Unit::_unit_value_type> x)
{
    return x.sqrt();
}
}  // namespace std
