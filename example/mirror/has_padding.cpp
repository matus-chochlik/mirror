/// @example mirror/has_padding.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/placeholder.hpp>
#include <mirror/sequence.hpp>

struct S1 {
    int i;
    float f;
};

struct S2 {
    char c;
    double d;
};

template <typename... T>
constexpr auto sum_sizeofs(mirror::type_list<T...>) {
    return (0Z + ... + sizeof(T));
}

template <typename T>
constexpr auto has_padding() -> bool {
    return sizeof(T) > sum_sizeofs(extract_types(transform(
                         get_data_members(mirror(T)), get_type(mirror::_1))));
}

template <typename T>
void print_has_padding() {
    std::cout << get_name(remove_all_aliases(mirror(T))) << ": "
              << (has_padding<T>() ? "has some" : "has no") << " padding"
              << std::endl;
}

int main() {
    print_has_padding<S1>();
    print_has_padding<S2>();
    return 0;
}
