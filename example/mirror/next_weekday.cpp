/// @example mirror/next_weekday.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/enum_utils.hpp>
#include <mirror/sequence.hpp>
#include <iostream>

enum class weekdays : int {
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

static weekdays next_day(weekdays d) {
    return weekdays((int(d) + 1) % 7);
}

static void print_next_day(std::string_view n) {
    if(auto opt_day{mirror::string_to_enum<weekdays>(n)}) {
        std::cout << n << " -> " << mirror::enum_to_string(next_day(*opt_day))
                  << std::endl;
    }
}

int main() {
    for_each(get_enumerators(mirror(weekdays)), [](auto mo) {
        print_next_day(get_name(mo));
    });

    return 0;
}
