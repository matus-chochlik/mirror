/// @example mirror/same_structure.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/hash.hpp>
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
    int j;
    float e;
    std::string z;
};

struct baz {
    long l;
    double d;
    char c;
    bool b;
};

int main() {
    using mirror::metaobject;
    auto have_same_structure = [](metaobject auto ml, metaobject auto mr) {
        using mirror::_1;
        const auto structure_hash =
          fold(get_data_members(_1), get_hash(get_type(_1)), [](auto... h) {
              return (... ^ h);
          });
        return structure_hash(ml) == structure_hash(mr);
    };

    std::cout << std::boolalpha << have_same_structure(mirror(foo), mirror(bar))
              << std::endl;
    std::cout << std::boolalpha << have_same_structure(mirror(foo), mirror(baz))
              << std::endl;
    return 0;
}
