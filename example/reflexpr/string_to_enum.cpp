/// @example string_to_enum.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <experimental/reflect>
#include <iostream>
#include <optional>
#include <string_view>

enum class weekdays {
    monday = 1,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

namespace meta = std::experimental::reflect;

template <typename E>
struct string_to_enum_helper {
    template <typename... MEC>
    struct _impl {
        static std::optional<E> find(std::string_view n) {
            return _do_find(n, MEC{}...);
        }

        template <typename ME1, typename... MEs>
        static std::optional<E> _do_find(std::string_view n, ME1, MEs... mes) {
            if(std::string_view{meta::get_name_v<ME1>} == n) {
                return {meta::get_constant_v<ME1>};
            }
            return _do_find(n, mes...);
        }

        static std::optional<E> _do_find(std::string_view) {
            return {};
        }
    };

    static std::optional<E> find(std::string_view n) {
        return meta::
          unpack_sequence_t<_impl, meta::get_enumerators_t<reflexpr(E)>>::find(
            n);
    }
};

template <typename E>
static std::optional<E> string_to_enum(std::string_view n) {
    return string_to_enum_helper<E>::find(n);
}

template <typename E>
void print(std::optional<E> d) {
    if(d) {
        std::cout << std::underlying_type_t<E>(*d) << std::endl;
    } else {
        std::cout << "N/A" << std::endl;
    }
}

int main() {
    print(string_to_enum<weekdays>("monday"));
    print(string_to_enum<weekdays>("tuesday"));
    print(string_to_enum<weekdays>("wednesday"));
    print(string_to_enum<weekdays>("thursday"));
    print(string_to_enum<weekdays>("friday"));
    print(string_to_enum<weekdays>("saturday"));
    print(string_to_enum<weekdays>("sunday"));

    return 0;
}
