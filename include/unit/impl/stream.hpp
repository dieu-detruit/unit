#pragma once

#include <unit/impl/core.hpp>
#include <unit/impl/dimension.hpp>
#include <unit/impl/literal.hpp>
#include <unit/impl/utility.hpp>

#include <iostream>
#include <string>
#include <type_traits>

namespace Unit
{
namespace Impl
{

// Use unique literal if it exists
template <Fundamental dim_type>
std::string dimension_to_str([[maybe_unused]] const dim_type&)
{
    return literal_of<dim_type>::get();
}

template <class dim_type>
struct cancel_denominator {
    static constexpr long den = get_dimensions<typename dim_type::dim_t>::den;
    using type = DimensionType<
        decltype(dim_type::dim_t::template pow<den>()),
        typename dim_type::value_t>;
};

template <class dim_type>
using cancel_denominator_t = typename cancel_denominator<dim_type>::type;

// Use unique literal if it exists
template <class dim_type>
requires Combinative<dim_type>&& Fundamental<cancel_denominator_t<dim_type>>
    std::string dimension_to_str([[maybe_unused]] const dim_type&)
{
    constexpr long den = cancel_denominator<dim_type>::den;
    return literal_of<cancel_denominator_t<dim_type>>::get() + "^(1/" + std::to_string(den) + ")";
}

#define SINGLE_DIM_TO_STR(var, den, dim, literal)                                                        \
    if constexpr (dim != 0) {                                                                            \
        if (dim == den) {                                                                                \
            var += #literal;                                                                             \
        } else if (dim % den == 0) {                                                                     \
            var += std::string(#literal) + "^" + std::to_string(dim / den);                              \
        } else {                                                                                         \
            constexpr long g = Impl::gcd(dim, den);                                                      \
            var += std::string(#literal) + "^(" + std::to_string(dim) + "/" + std::to_string(den) + ")"; \
        }                                                                                                \
    }

template <class dim_type>
requires Combinative<dim_type>&& Combinative<cancel_denominator_t<dim_type>>
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
