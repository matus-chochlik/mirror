/// @example mirror/test.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/ctre_match.hpp>
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

int main() {
    using mirror::_1;
    const auto highest_arity_overload = find_ranking(
      filter(get_member_functions(_1), ctre_match<"plus">(get_name(_1))),
      get_size(get_parameters(_1)));

    std::cout << '('
              << join_to_string(
                   get_parameters(highest_arity_overload(mirror(foo))),
                   get_display_name(get_type(_1)),
                   ", ")
              << ')' << std::endl;

    return 0;
}
