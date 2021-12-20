/// @example mirror/row_polymorphism.cpp
///
/// Copyright Kris Jusiak, Matus Chochlik
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/sequence.hpp>
#include <iostream>
#include <string>
#include <string_view>

template <auto Size>
struct fixed_string {
    char data[Size + 1]{};
    static constexpr auto size = Size;

    constexpr explicit(false) fixed_string(char const* str) {
        std::copy_n(str, Size + 1, data);
    }
    constexpr explicit(false) operator std::string_view() const {
        return {data, Size};
    }
};
template <auto Size>
fixed_string(char const (&)[Size]) -> fixed_string<Size - 1>;

template <fixed_string Name, class TValue = void*>
struct row {
    static constexpr auto name = Name;
    TValue value{};
    template <class T>
    constexpr auto operator=(const T& t) {
        return row<Name, T>{.value = t};
    }
};

template <fixed_string Name>
constexpr auto operator""_row() {
    return row<Name>{};
}

template <class T, fixed_string Name>
concept has_member_name = []<class... Ts>(mirror::type_list<Ts...>) {
    return ((get_name(Ts{}) == Name) or ...);
}
(expand(get_data_members(mirror(T))));

template <class... Ts>
struct rows : Ts... {
    template <class T>
    requires(has_member_name<T, Ts::name>and...) explicit(false)
      rows(const T& t) {
        (
          [&] {
              for_each(get_data_members(get_aliased(mirror(T))), [&](auto mo) {
                  if(Ts::name == get_name(mo)) {
                      Ts::value = get_value(mo, t);
                  }
              });
          }(),
          ...);
    }

    template <class T>
    constexpr decltype(auto) operator[](T) {
        return get<T::name>(*this);
    }

private:
    template <fixed_string Name, class T>
    constexpr decltype(auto) get(row<Name, T>& t) {
        return (t.value);
    }
};

static auto shrink(rows<row<"a", int>, row<"b", int>> t) {
    std::cout << t["a"_row] << ", " << t["b"_row] << '\n';
}

int main() {
    struct empty {};
    struct nope {
        int a{};
    };
    struct foo {
        int a{};
        int b{};
    };
    struct bar {
        int c{};
        int b{};
        int a{};
    };

    static_assert(not [](auto t) {
        return requires {
            shrink(t);
        };
    }(empty{}));
    static_assert(not [](auto t) {
        return requires {
            shrink(t);
        };
    }(nope{}));
    static_assert([](auto t) {
        return requires {
            shrink(t);
        };
    }(foo{}));
    static_assert([](auto t) {
        return requires {
            shrink(t);
        };
    }(bar{}));

    shrink(foo{.a = 1, .b = 2});         // prints 1, 2
    shrink(bar{.c = 8, .b = 4, .a = 2}); // prints 2, 4
}
