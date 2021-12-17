/// @example print_months.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iomanip>
#include <iostream>
#include <mirror/make_array.hpp>
#include <tuple>

enum class month : int {
    january = 1,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
};

int main() {
    const auto info = make_array(get_enumerators(mirror(month)), [](auto me) {
        return std::make_tuple(get_constant(me), get_name(me));
    });
    for(const auto& [value, name] : info) {
        std::cout << std::setw(2) << int(value) << ": " << name << std::endl;
    }
    return 0;
}
