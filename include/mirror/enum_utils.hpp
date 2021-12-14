/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_ENUM_UTILS_HPP
#define MIRROR_ENUM_UTILS_HPP

#include "primitives.hpp"
#include <optional>

namespace mirror {

template <typename E>
auto enum_to_string(E e) noexcept -> string_view {
    return select(
      get_enumerators(mirror(E)),
      [](auto& result, auto mo, auto c) {
          if(get_constant(mo) == c) {
              result = get_name(mo);
          }
      },
      string_view{},
      e);
}

template <typename E>
auto string_to_enum(string_view s) noexcept -> std::optional<E> {
    return select(
      get_enumerators(mirror(E)),
      [](auto& result, auto mo, auto n) {
          if(get_name(mo) == n) {
              result = get_constant(mo);
          }
      },
      std::optional<E>{},
      s);
}

} // namespace mirror

#endif // MIRROR_ENUM_UTILS_HPP

