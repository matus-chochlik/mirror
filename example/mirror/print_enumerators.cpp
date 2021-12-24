/// @example mirror/print_enumerators.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/weekday.hpp"
#include <mirror/enum_utils.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

int main() {
    for_each(get_enumerators(mirror(example::weekday)), [](auto mo) {
        std::cout << get_name(mo) << ": " << int(get_constant(mo)) << std::endl;
    });
    return 0;
}
