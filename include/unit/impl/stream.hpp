#include "unit/impl/core.hpp"
#include "unit/impl/literal.hpp"
#include "unit/impl/type_traits.hpp"

#include <iostream>
#include <string>
#include <type_traits>

namespace Unit
{
namespace Impl
{

template <class dim_type, ONLY_IF(has_literal<dim_type>::value)>
std::string dimension_to_str([[maybe_unused]] const dim_type&)
{
    return literal_of<dim_type>::get();
}

#define SINGLE_DIM_TO_STR(var, dim, literal)                      \
    if constexpr (dim == 1) {                                     \
        var += #literal;                                          \
    } else if (dim != 0) {                                        \
        var += std::string(#literal) + "^" + std::to_string(dim); \
    }

template <int M, int K, int S, int A, typename T, ONLY_IF((not has_literal<DimensionType<Dim<M, K, S, A>, T>>::value))>
std::string dimension_to_str([[maybe_unused]] const DimensionType<Dim<M, K, S, A>, T>&)
{
    std::string str;

    SINGLE_DIM_TO_STR(str, M, m);
    SINGLE_DIM_TO_STR(str, K, kg);
    SINGLE_DIM_TO_STR(str, S, s);
    SINGLE_DIM_TO_STR(str, A, A);

    return str;
}

}  // namespace Impl


template <class dim, typename T>
inline std::ostream& operator<<(std::ostream& os, const DimensionType<dim, T>& right)
{
    os << right.value << ' ' << Impl::dimension_to_str(right);
    return os;
}

}  // namespace Unit
