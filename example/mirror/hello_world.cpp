/// @example mirror/hello_world.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/primitives.hpp>
#include <iostream>

struct hello {};

int main() {
    hello world;
    (void)world;

    std::cout << get_name(mirror(hello)) << ", " << get_name(mirror(world))
              << std::endl;

    return 0;
}
