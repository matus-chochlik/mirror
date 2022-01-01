/// @example mirror/applicable_ops.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include "testdecl/weekday.hpp"
#include <mirror/operations.hpp>
#include <mirror/sequence.hpp>
#include <iostream>
#include <string>

void print_info(mirror::metaobject auto mo) {
    const auto mes = concat(
      get_enumerators(mirror(mirror::unary_op_boolean)),
      get_enumerators(mirror(mirror::unary_op_integer)),
      get_enumerators(mirror(mirror::unary_op_pointer)),
      get_enumerators(mirror(mirror::unary_op_string)),
      get_enumerators(mirror(mirror::unary_op_metaobject)));

    std::cout << "operations applicable to " << get_display_name(mo)
              << std::endl;
    for_each(mes, [&](mirror::metaobject auto me) {
        if(is_applicable<get_constant(me)>(mo)) {
            std::cout << "  " << get_name(me) << std::endl;
        }
    });
    std::cout << std::endl;
}

int main(int argc, const char**) {
    print_info(mirror(int));
    print_info(mirror(std));
    print_info(mirror(std::string));
    print_info(mirror(argc));
    print_info(mirror(example::weekday));
    print_info(mirror(example::weekday::friday));
    return argc - 1;
}
