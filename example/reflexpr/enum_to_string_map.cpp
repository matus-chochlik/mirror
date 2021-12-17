/// @example enum_to_string_map.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <experimental/reflect>
#include <iostream>
#include <map>
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

template <typename E>
class enum_to_string {
public:
    std::string_view operator()(E e) const {
        const auto pos = _map.find(e);
        if(pos != _map.end()) {
            return pos->second;
        }
        return {};
    }

private:
    template <typename... MEC>
    struct helper {
        static auto make_map() {
            std::map<E, std::string_view> res;
            (...,
             res.emplace(meta::get_constant_v<MEC>, meta::get_name_v<MEC>));
            return res;
        }
    };

    static auto _make_map() {
        return meta::unpack_sequence_t<
          helper,
          meta::get_enumerators_t<reflexpr(E)>>::make_map();
    }
    const std::map<E, std::string_view> _map{_make_map()};
};

int main() {
    const enum_to_string<weekdays> ets;

    std::cout << ets(weekdays::monday) << std::endl;
    std::cout << ets(weekdays::tuesday) << std::endl;
    std::cout << ets(weekdays::wednesday) << std::endl;
    std::cout << ets(weekdays::thursday) << std::endl;
    std::cout << ets(weekdays::friday) << std::endl;
    std::cout << ets(weekdays::saturday) << std::endl;
    std::cout << ets(weekdays::sunday) << std::endl;

    return 0;
}
