/// @example mirror/print_op_results.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/init_list.hpp>
#include <mirror/operations.hpp>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

static void print_value(std::optional<std::string_view> value) {
    if(value) {
        std::cout << std::quoted(*value);
    } else {
        std::cout << "N/A";
    }
}

static void print_value(std::optional<bool> value) {
    if(value) {
        std::cout << std::boolalpha << *value;
    } else {
        std::cout << "N/A";
    }
}

template <typename T>
static void print_value(std::optional<T> value) requires(std::is_integral_v<T>) {
    if(value) {
        std::cout << *value;
    } else {
        std::cout << "N/A";
    }
}

template <typename T>
static void print_value(std::optional<T> value) requires(mirror::metaobject<T>) {
    if(value) {
        std::cout << "metaobject(" << get_id(*value) << ")";
    } else {
        std::cout << "N/A";
    }
}

void print_info(mirror::metaobject auto mo) {
    const auto mes = get_enumerators(mirror(mirror::metaobject_unary_op));
    const auto maxl = fold_init_list(
      mes,
      [](auto me) { return get_name(me).size(); },
      [](auto l) { return std::max(l); });

    std::cout << "meta-info for " << get_display_name(mo) << std::endl;
    for_each(mes, [&](mirror::metaobject auto me) {
        std::cout << "  " << get_name(me) << ": "
                  << std::string(maxl - get_name(me).size(), ' ');
        print_value(try_apply<get_constant(me)>(mo));
        std::cout << std::endl;
    });
    std::cout << std::endl;
}

int main(int argc, const char**) {
    print_info(mirror(int));
    print_info(mirror(std));
    print_info(mirror(std::string));
    print_info(mirror(argc));
    return argc - 1;
}
