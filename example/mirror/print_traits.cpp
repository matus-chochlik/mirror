/// @example mirror/print_traits.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/weekday.hpp"
#include <mirror/init_list.hpp>
#include <mirror/placeholder.hpp>
#include <mirror/traits.hpp>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

void print_traits(mirror::metaobject auto mo) {
    const auto mes = get_enumerators(mirror(mirror::meta_trait));
    const auto maxl = fold_init_list(
      mes, get_size(get_name(mirror::_1)), [](auto l) { return std::max(l); });

    std::cout << "traits of " << get_display_name(mo) << std::endl;
    for_each(mes, [&](mirror::metaobject auto me) {
        std::cout << "  " << get_name(me) << ": " << std::boolalpha
                  << std::string(maxl - get_name(me).size(), ' ')
                  << has_trait<get_constant(me)>(mo) << std::endl;
    });
    std::cout << std::endl;
}

int main(int argc, const char**) {
    print_traits(mirror(int));
    print_traits(mirror(std));
    print_traits(mirror(std::string));
    print_traits(mirror(argc));
    print_traits(mirror(example::weekday));
    print_traits(mirror(example::weekday::friday));
    return argc - 1;
}
