/// @example mirror/are_consecutive.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

enum class digits {
    zero = 0,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine
};

enum class po2s {
    one = 1,
    two = 2,
    four = 4,
    eight = 8,
    sixteen = 16,
    thirty_two = 32
};

int main() {
    const auto are_consecutive =
      is_sorted(get_enumerators(mirror::_1), [](auto l, auto r) {
          return int(get_constant(l)) + 1 == int(get_constant(r));
      });

    std::cout << are_consecutive(mirror(digits)) << std::endl;
    std::cout << are_consecutive(mirror(po2s)) << std::endl;

    return 0;
}
