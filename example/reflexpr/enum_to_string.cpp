/// @example enum_to_string
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <experimental/reflect>
#include <iostream>
#include <string_view>

enum class weekdays {
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

namespace meta = std::experimental::reflect;

template <typename... MEC>
struct enum_to_string_helper {
    template <typename E>
    static std::string_view find(E e) {
        return _do_find(e, MEC{}...);
    }

    template <typename E, typename ME1, typename... MEs>
    static std::string_view _do_find(E e, ME1, MEs... mes) {
        if(meta::get_constant_v<ME1> == e) {
            return {meta::get_name_v<ME1>};
        }
        return _do_find(e, mes...);
    }

    template <typename E>
    static std::string_view _do_find(E) {
        return {};
    }
};

template <typename E>
std::string_view enum_to_string(E e) {
    return meta::unpack_sequence_t<
      enum_to_string_helper,
      meta::get_enumerators_t<reflexpr(E)>>::find(e);
}

int main() {
    std::cout << enum_to_string(weekdays::monday) << std::endl;
    std::cout << enum_to_string(weekdays::tuesday) << std::endl;
    std::cout << enum_to_string(weekdays::wednesday) << std::endl;
    std::cout << enum_to_string(weekdays::thursday) << std::endl;
    std::cout << enum_to_string(weekdays::friday) << std::endl;
    std::cout << enum_to_string(weekdays::saturday) << std::endl;
    std::cout << enum_to_string(weekdays::sunday) << std::endl;

    return 0;
}
