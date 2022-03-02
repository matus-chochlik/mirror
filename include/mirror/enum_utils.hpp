/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_ENUM_UTILS_HPP
#define MIRROR_ENUM_UTILS_HPP

#include "placeholder.hpp"
#include "primitives.hpp"
#include <optional>

namespace mirror {

/// @brief Returns the name of the specified enumerator.
/// @ingroup utilities
/// @see string_to_enum
template <typename E>
auto enum_to_string(E e) noexcept -> string_view {
    return choose(
      std::string_view{},
      get_enumerators(mirror(E)),
      has_value(_1, e),
      get_name(_1));
}

/// @brief Finds the value of enum type @c E with the specified name.
/// @ingroup utilities
/// @see enum_to_string
template <typename E>
auto string_to_enum(string_view s) noexcept -> std::optional<E> {
    return choose(
      std::optional<E>{},
      get_enumerators(mirror(E)),
      has_name(_1, s),
      get_value(_1));
}

} // namespace mirror

#endif // MIRROR_ENUM_UTILS_HPP

