/// @example mirror/filter.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/tetrahedron.hpp"
#include <mirror/sequence.hpp>
#include <iostream>

int main() {
    for_each(
      make_sequence(
        mirror(example::vector),
        mirror(example::triangle),
        mirror(example::tetrahedron)),
      [](mirror::metaobject auto mo) {
          std::cout << "member functions without parameters: ";
          for_each(
            filter(
              get_member_functions(mo),
              [](auto mf) { return is_empty(get_parameters(mf)); }),
            [](auto mf) { std::cout << get_name(mf) << "; "; });
          std::cout << std::endl;
      });

    return 0;
}
