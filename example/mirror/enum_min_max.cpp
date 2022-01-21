/// @example mirror/enum_min_max.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/month.hpp"
#include "testdecl/weekday.hpp"
#include <mirror/enum_utils.hpp>
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <functional>
#include <iostream>

int main() {
    using mirror::_1;
    using mirror::enum_to_string;

    auto min_enum =
      get_top_value(get_enumerators(_1), get_constant(_1), std::greater<>{});
    auto max_enum =
      get_top_value(get_enumerators(_1), get_constant(_1), std::less<>{});

    auto print_info = [&](auto me) {
        std::cout << get_name(me) << ": min(" << enum_to_string(min_enum(me))
                  << "), max(" << enum_to_string(max_enum(me)) << ")"
                  << std::endl;
    };

    print_info(mirror(example::month));
    print_info(mirror(example::weekday));

    return 0;
}
