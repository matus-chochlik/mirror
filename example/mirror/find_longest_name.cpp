/// @example mirror/find_longest_name.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/month.hpp"
#include "testdecl/weekday.hpp"
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

void print_info(mirror::metaobject auto mo) {
    const auto find_enum_with_longest_name =
      find_ranking(get_enumerators(mirror::_1), get_size(get_name(mirror::_1)));

    const auto me = find_enum_with_longest_name(mo);

    std::cout << get_name(me) << ", length: " << get_name(me).size()
              << ", value: " << int(get_constant(me)) << std::endl;
}

int main() {
    print_info(mirror(example::weekday));
    print_info(mirror(example::month));

    return 0;
}
