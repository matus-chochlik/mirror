/// @example mirror/ctre_integer_concept.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <mirror/ctre_match.hpp>
#include <mirror/primitives.hpp>
#include <iostream>

template <typename T>
concept very_smart_integer = mirror::ctre_match<
  "((signed|unsigned) )?((long long|long|short)( int)?|int)">(
  get_name(remove_all_aliases(mirror(T))));

auto add(very_smart_integer auto l, very_smart_integer auto r) {
    return l + r;
}

int main() {
    std::cout << add(1U, 2U) << std::endl;
    std::cout << add(short(3), short(4)) << std::endl;
    std::cout << add(21, 21) << std::endl;
    std::cout << add(400ULL, 20ULL) << std::endl;

    return 0;
}
