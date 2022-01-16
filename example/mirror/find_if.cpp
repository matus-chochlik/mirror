/// @example mirror/find_if.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

struct mystruct {
    using type = char;

    std::string s{"str"};
    float f{1.2F};
    int i{345};
    bool b{false};

    mystruct() = default;
};

int main() {
    using mirror::_1;
    mystruct x;

    const auto ms = mirror(mystruct);

    const auto found_by_name =
      find_if(get_data_members(ms), [](auto me) { return has_name(me, "i"); });

    if(reflects_variable(found_by_name)) {
        std::cout << get_value(found_by_name, x) << std::endl;
    }

    const auto found_by_having_type =
      find_if(get_data_members(ms), has_type<std::string>(_1));

    if(reflects_variable(found_by_having_type)) {
        std::cout << get_value(found_by_having_type, x) << std::endl;
    }

    const auto found_by_having_trait = find_if(
      get_data_members(ms), has_type_with_trait<std::is_floating_point>(_1));

    if(reflects_variable(found_by_having_trait)) {
        std::cout << get_value(found_by_having_trait, x) << std::endl;
    }

    const auto found_by_being_type =
      find_if(get_member_types(ms), is_type<char>(_1));

    if(reflects_type(found_by_being_type)) {
        std::cout << get_name(found_by_being_type) << std::endl;
    }

    const auto found_default_ctr = find_if(
      transform(get_constructors(ms), get_parameters(_1)), is_empty(_1));

    if(reflects_object(found_default_ctr)) {
        std::cout << "has default constructor" << std::endl;
    }

    const auto found_nondefault_ctr = find_if_not(
      transform(get_constructors(ms), get_parameters(_1)), is_empty(_1));

    if(reflects_object(found_nondefault_ctr)) {
        std::cout << "has non-default constructor" << std::endl;
    }
    return 0;
}
