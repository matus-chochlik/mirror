/// @example mirror/are_sorted_by_size.cpp
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
    const auto are_sorted_by_size = is_sorted(
      get_data_members(mirror::_1),
      get_sizeof(get_type(mirror::_1)) < get_sizeof(get_type(mirror::_2)));

    std::cout << are_sorted_by_size(mirror(foo)) << std::endl;
    std::cout << are_sorted_by_size(mirror(bar)) << std::endl;

    return 0;
}
