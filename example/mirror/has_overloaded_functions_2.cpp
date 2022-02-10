/// @example mirror/has_overloaded_functions_2.cpp
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
    int plus(int x) {
        return x;
    }
    int plus(int x, int y) {
        return x + y;
    }
    int plus(int x, int y, int z) {
        return x + y + z;
    }
    int minus(int x) {
        return -x;
    }
    int minus(int x, int y) {
        return x - y;
    }
};

struct bar {
    int a() {
        return 0;
    }
    int b() {
        return 1;
    }
    int c() {
        return 2;
    }
};

int main() {
    using mirror::_1;
    const auto has_overloaded_functions = any_of(
      group_by(get_member_functions(_1), get_name(_1)),
      has_multiple_elements(_1));

    std::cout << has_overloaded_functions(mirror(foo)) << std::endl;
    std::cout << has_overloaded_functions(mirror(bar)) << std::endl;

    return 0;
}
