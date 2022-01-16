/// @example mirror/remove_if.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/tetrahedron.hpp"
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

int main() {
    for_each(
      make_sequence(
        mirror(example::vector),
        mirror(example::triangle),
        mirror(example::tetrahedron)),
      [](mirror::metaobject auto mo) {
          std::cout << "non-static member functions: ";
          std::cout << join(
            remove_if(get_member_functions(mo), is_static(mirror::_1)),
            to_string(get_name(mirror::_1)),
            std::string("; "));
          std::cout << std::endl;
      });

    for_each(
      make_sequence(
        mirror(example::vector),
        mirror(example::triangle),
        mirror(example::tetrahedron)),
      [](mirror::metaobject auto mo) {
          std::cout << "count of constructors with parameters: ";
          std::cout << get_size(remove_if(
            get_constructors(mo), is_empty(get_parameters(mirror::_1))));
          std::cout << std::endl;
      });

    return 0;
}
