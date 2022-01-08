/// @example mirror/amount_of_foo.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/ctre_match.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

struct meh {};

struct foo {
    foo() noexcept = default;
};

struct qux {
    void foo() {}
    auto foo(int i) {
        return i;
    }
    auto foo(int l, int r) {
        return l + r;
    }
    void bar() {}
    void baz() {}
};

void compare_by_foo(mirror::metaobject auto l, mirror::metaobject auto r) {
    using mirror::_1;
    const auto amount_of_foo = get_size(filter(
      flatten(make_sequence(get_constructors(_1), get_member_functions(_1))),
      ctre_match<"^foo$">(get_name(_1))));

    const auto name_of = get_name(remove_all_aliases(_1));

    if(amount_of_foo(l) > amount_of_foo(r)) {
        std::cout << name_of(l) << " has more foo than " << name_of(r);
    } else if(amount_of_foo(l) < amount_of_foo(r)) {
        std::cout << name_of(l) << " has less foo than " << name_of(r);
    } else {
        std::cout << name_of(l) << " and " << name_of(r)
                  << " have equal amount of foo";
    }
    std::cout << std::endl;
}

int main() {

    compare_by_foo(mirror(foo), mirror(meh));
    compare_by_foo(mirror(foo), mirror(foo));
    compare_by_foo(mirror(foo), mirror(qux));

    return 0;
}
