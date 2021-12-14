/// @example print_full_name
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/full_name.hpp>

namespace calendar {

enum class weekday : int {
    monday = 1,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

} // namespace calendar

int main() {
    std::cout << get_full_name(mirror(calendar::weekday)) << std::endl;
    std::cout << get_full_name(mirror(calendar::weekday::monday)) << std::endl;
    std::cout << get_full_name(mirror(int)) << std::endl;
    std::cout << get_full_name(mirror(int&)) << std::endl;
    std::cout << get_full_name(mirror(int**)) << std::endl;
    std::cout << get_full_name(mirror(int volatile* const*)) << std::endl;
    std::cout << get_full_name(mirror(int*[][1][2][3])) << std::endl;
    std::cout << get_full_name(mirror(const std::string&)) << std::endl;
    std::cout << get_full_name(mirror(int(float, bool) noexcept)) << std::endl;

    using F1 = void();
    std::cout << get_full_name(mirror(F1)) << std::endl;

    using F2 = F1*(bool) noexcept;
    std::cout << get_full_name(mirror(F2)) << std::endl;

    using F3 = F2*(int&, float volatile* const*);
    (void)sizeof(F3*);
    std::cout << get_full_name(mirror(F3)) << std::endl;

    return 0;
}
