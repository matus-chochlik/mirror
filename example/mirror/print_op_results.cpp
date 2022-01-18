/// @example mirror/print_op_results.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/extract.hpp>
#include <mirror/init_list.hpp>
#include <mirror/operations.hpp>
#include <mirror/placeholder.hpp>
#include <algorithm>
#include <concepts>
#include <iomanip>
#include <iostream>
#include <string>

static void do_print_value(std::string_view value) {
    std::cout << std::quoted(value);
}

static void do_print_value(bool value) {
    std::cout << std::boolalpha << value;
}

static void do_print_value(std::integral auto value) {
    std::cout << value;
}

static void print_value(mirror::metaobject auto value) {
    if(reflects_object(value)) {
        std::cout << "metaobject(" << get_id(value) << ")";
    } else {
        std::cout << "no_metaobject";
    }
}

static void print_value(auto opt_value) {
    using mirror::has_value;
    if(has_value(opt_value)) {
        using mirror::extract;
        do_print_value(extract(opt_value));
    } else {
        std::cout << "N/A";
    }
}

void print_info(mirror::metaobject auto mo) {
    const auto mes = flatten(transform(
      mirror::all_metaobject_operation_kinds(), get_enumerators(mirror::_1)));

    const auto maxl = fold_init_list(
      mes, get_size(get_name(mirror::_1)), [](auto l) { return std::max(l); });

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
