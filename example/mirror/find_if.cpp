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
    using type = char;

    std::string s{"str"};
    float f{1.2F};
    int i{345};
    bool b{false};

    mystruct() = default;
};

int main() {
    mystruct x;

    const auto found_by_name = find_if(
      get_data_members(mirror(mystruct)),
      [](auto me) { return has_name(me, "f"); });

    if(reflects_variable(found_by_name)) {
        std::cout << get_value(found_by_name, x) << std::endl;
    }

    const auto found_by_having_type = find_if(
      get_data_members(mirror(mystruct)),
      [](auto me) { return has_type<std::string>(me); });

    if(reflects_variable(found_by_having_type)) {
        std::cout << get_value(found_by_having_type, x) << std::endl;
    }

    const auto found_by_being_type = find_if(
      get_member_types(mirror(mystruct)),
      [](auto me) { return is_type<char>(me); });

    if(reflects_type(found_by_being_type)) {
        std::cout << get_name(found_by_being_type) << std::endl;
    }

    const auto found_default_ctr = find_if(
      get_constructors(mirror(mystruct)),
      [](auto me) { return is_empty(get_parameters(me)); });

    if(reflects_object(found_default_ctr)) {
        std::cout << "has default constructor" << std::endl;
    }
    return 0;
}
