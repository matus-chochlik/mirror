/// @example mirror/has_overloaded_functions.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
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
    const auto has_overloaded_functions = [](auto mo) {
        const auto mfs = get_member_functions(mo);
        return fold(
          mfs,
          [mfs](auto mf1) {
              return any_of(mfs, [mf1](auto mf2) {
                  return !reflects_same(mf1, mf2) &&
                         get_name(mf1) == get_name(mf2);
              });
          },
          [](auto... b) { return (... || b); });
    };

    std::cout << has_overloaded_functions(mirror(foo)) << std::endl;
    std::cout << has_overloaded_functions(mirror(bar)) << std::endl;

    return 0;
}
