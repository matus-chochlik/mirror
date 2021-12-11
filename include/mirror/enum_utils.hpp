/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_ALL_HPP
#define MIRROR_ALL_HPP

#include "primitives.hpp"

namespace mirror {

template <typename E>
string_view enum_to_string(E e) {
  return select(get_enumerators(mirror(E)),
    [](auto& result, auto mo, auto c) {
      if (get_constant(mo) == c) {
        result = get_name(mo);
      }
    }, string_view{}, e);
}

template <typename E>
E string_to_enum(string_view s) {
  return select(get_enumerators(mirror(E)),
    [](auto& result, auto mo, auto n) {
      if (get_name(mo) == n) {
        result = get_constant(mo);
      }
    }, E{}, s);
}

} // namespace mirror

#endif // MIRROR_ALL_HPP

