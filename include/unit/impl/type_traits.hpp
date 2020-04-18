#pragma once

#include <type_traits>

namespace Unit
{

#define ONLY_IF(cond) std::enable_if_t<cond, std::nullptr_t> = nullptr
#define PROHIBIT(cond) std::enable_if_t<cond, std::nullptr_t> = nullptr

template <typename value_type, typename arg_type>
inline constexpr bool is_multiplicable_v
    = std::is_floating_point_v<arg_type>and std::is_convertible_v<arg_type, value_type>;


}  // namespace Unit