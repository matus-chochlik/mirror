/// @example mirror/good_example.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <mirror/ctre_match.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

struct excellent_example {
    void foo() {}
    void bar() {}
    void baz() {}
};

struct good_example {
    void qux() {}
    void baz() {}
};

struct bad_example {
    void my_function() {}
};

template <typename T>
concept good_example_class = any_of(
  get_member_functions(mirror(T)),
  ctre_match<"foo|bar|baz">(get_name(mirror::_1)));

void review(good_example_class auto) {
    std::cout << "what a nice example!\n";
}

void review(auto) {
    std::cout << "try harder...\n";
}

int main() {
    review(excellent_example{});
    review(good_example{});
    review(bad_example{});

    return 0;
}
