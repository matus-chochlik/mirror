/// @example mirror/print_full_name.cpp
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

struct event {
    weekday get_day() const {
        return _day;
    }

    void set_time(int hour, int minute) noexcept {
        _hour = hour;
        _minute = minute;
    }

    weekday _day{weekday::monday};
    int _hour{0};
    int _minute{0};
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

    using M1 = decltype(&calendar::event::get_day);
    std::cout << get_full_name(mirror(M1)) << std::endl;

    using F4 = M1*(std::string);
    (void)sizeof(F4*);
    std::cout << get_full_name(mirror(F4*)) << std::endl;

    using M2 = decltype(&calendar::event::set_time);
    std::cout << get_full_name(mirror(M2)) << std::endl;

    using F5 = M2(calendar::event) noexcept;
    (void)sizeof(F5*);
    std::cout << get_full_name(mirror(F5*)) << std::endl;

    using A1 = decltype(&calendar::event::_day);
    std::cout << get_full_name(mirror(A1)) << std::endl;

    using F6 = A1(float);
    (void)sizeof(F6*);
    std::cout << get_full_name(mirror(F6*)) << std::endl;

    return 0;
}
