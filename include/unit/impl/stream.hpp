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

#define SINGLE_DIM_TO_STR(var, den, dim, literal)                                                        \
    if constexpr (dim != 0) {                                                                            \
        if (dim == den) {                                                                                \
            var += #literal;                                                                             \
        } else if (dim % den == 0) {                                                                     \
            var += std::string(#literal) + "^" + std::to_string(dim / den);                              \
        } else {                                                                                         \
            constexpr int g = Impl::gcd(dim, den);                                                       \
            var += std::string(#literal) + "^(" + std::to_string(dim) + "/" + std::to_string(den) + ")"; \
        }                                                                                                \
    }

template <class dim_type, ONLY_IF(not has_literal<dim_type>::value)>
std::string dimension_to_str([[maybe_unused]] const dim_type&)
{
    std::string str;

    using dims = get_dimensions<typename dim_type::dim_t>;

    SINGLE_DIM_TO_STR(str, dims::den, dims::L, m);
    SINGLE_DIM_TO_STR(str, dims::den, dims::M, kg);
    SINGLE_DIM_TO_STR(str, dims::den, dims::T, s);
    SINGLE_DIM_TO_STR(str, dims::den, dims::Theta, K);
    SINGLE_DIM_TO_STR(str, dims::den, dims::N, mol);
    SINGLE_DIM_TO_STR(str, dims::den, dims::I, A);
    SINGLE_DIM_TO_STR(str, dims::den, dims::J, cd);

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
