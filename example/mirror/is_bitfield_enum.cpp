/// @example mirror/is_bitfield_enum.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/weekday.hpp"
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iostream>
#include <type_traits>

int main() {
    const auto is_bitfield_enum =
      is_sorted(get_enumerators(mirror::_1), [](auto l, auto r) {
          if constexpr(has_type_trait<std::is_signed>(get_type(l))) {
              return false;
          } else {
              auto to_underlying = [](auto e) {
                  return static_cast<std::underlying_type_t<decltype(e)>>(e);
              };
              return to_underlying(get_constant(l)) << 1U ==
                     to_underlying(get_constant(r));
          }
      });

    std::cout << is_bitfield_enum(mirror(example::weekday_bit)) << std::endl;
    std::cout << is_bitfield_enum(mirror(example::weekday)) << std::endl;

    return 0;
}
