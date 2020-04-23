#pragma once

#include "unit/impl/core.hpp"
#include "unit/impl/dimension.hpp"
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

template <class dim_type, ONLY_IF(not has_literal<dim_type>::value)>
std::string dimension_to_str([[maybe_unused]] const dim_type&)
{
    std::string str;

    using dims = get_dimensions<typename dim_type::dim_t>;

    SINGLE_DIM_TO_STR(str, dims::L, m);
    SINGLE_DIM_TO_STR(str, dims::M, kg);
    SINGLE_DIM_TO_STR(str, dims::T, s);
    SINGLE_DIM_TO_STR(str, dims::Theta, K);
    SINGLE_DIM_TO_STR(str, dims::N, mol);
    SINGLE_DIM_TO_STR(str, dims::I, A);
    SINGLE_DIM_TO_STR(str, dims::J, cd);

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
