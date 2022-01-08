/// @example mirror/good_example.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <mirror/ctre_all.hpp>
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
concept good_example_class =
  any_of(get_member_functions(mirror(T)), [](mirror::metaobject auto mo) {
      return ctre::match<"foo|bar|baz">(get_name(mo));
  });

void showoff(good_example_class auto) {
    std::cout << "what a nice example!\n";
}

void showoff(auto) {
    std::cout << "try harder...\n";
}

int main() {
    showoff(excellent_example{});
    showoff(good_example{});
    showoff(bad_example{});

    return 0;
}
