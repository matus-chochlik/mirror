/// @example mirror/group_by.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/interface.hpp>
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

struct my_interface : mirror::interface<my_interface> {
    static auto name() {
        return get_name(mirror(my_interface));
    }

    virtual auto foo(int i, int j) -> int = 0;

    auto foo(int i) {
        return foo(i, 1);
    }

    virtual auto bar(int i, int j) -> int = 0;

    auto bar(int j) {
        return bar(1, j);
    }

    auto bar() {
        return bar(1, 2);
    }
};

int main() {
    using mirror::_1;

    const auto print_name = [](auto mo) {
        std::cout << get_name(mo) << "\n";
    };

    const auto mfs = get_member_functions(mirror(my_interface));

    auto [static_, non_static] = group_by(mfs, is_static(_1));

    std::cout << "\nstatic functions:\n";
    for_each(static_, print_name);

    std::cout << "\nnon static functions:\n";
    for_each(non_static, print_name);

    auto [virtual_, non_virtual] = group_by(mfs, is_virtual(_1));

    std::cout << "\nvirtual functions:\n";
    for_each(virtual_, print_name);

    std::cout << "\nnon virtual functions:\n";
    for_each(non_virtual, print_name);

    std::cout << "\noverload sets:\n";
    for_each(group_by(mfs, get_name(_1)), [&](auto mo) {
        std::cout << get_name(get_element<0>(mo)) << ": (" << get_size(mo)
                  << ")\n";
    });

    return 0;
}
