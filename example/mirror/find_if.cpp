/// @example find_if
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/primitives.hpp>

struct mystruct {
    std::string s{"str"};
    float f{1.2F};
    int i{345};
    bool b{false};
};

int main() {
    mystruct x;

    const auto found_by_name = find_if(
      get_data_members(mirror(mystruct)),
      [](auto me) { return has_name(me, "f"); });

    if(reflects_variable(found_by_name)) {
        std::cout << get_value(found_by_name, x) << std::endl;
    }

    const auto found_by_type = find_if(
      get_data_members(mirror(mystruct)),
      [](auto me) { return has_type<std::string>(me); });

    if(reflects_variable(found_by_type)) {
        std::cout << get_value(found_by_type, x) << std::endl;
    }
    return 0;
}
