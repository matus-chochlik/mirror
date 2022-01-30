/// @example mirror/integral_data_members.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

struct foo {
    double d;
    int i;
    short s;
    char c;
};

struct bar {
    int i;
    float f;
    long l;
    bool b;
};

int main() {
    const auto count_integral_members = count_if(
      get_data_members(mirror::_1),
      has_type_trait<std::is_integral>(get_type(mirror::_1)));

    std::cout << count_integral_members(mirror(foo)) << std::endl;
    std::cout << count_integral_members(mirror(bar)) << std::endl;

    return 0;
}
