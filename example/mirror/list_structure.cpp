/// @example mirror/list_structure.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/full_name.hpp>
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iomanip>
#include <iostream>
#include <string>

struct foo {
    int i;
    float f;
    std::string s;
};

struct bar {
    long l;
    double d;
    char c;
    bool b;
};

int main() {
    using mirror::_1;
    const auto get_type_name_list =
      join(get_data_members(_1), get_full_name(get_type(_1)), ", ");

    std::cout << '{' << get_type_name_list(mirror(foo)) << '}' << std::endl;
    std::cout << '{' << get_type_name_list(mirror(bar)) << '}' << std::endl;
    return 0;
}
