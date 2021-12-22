/// @example reflexpr/named_parameters.cpp
///
/// Copyright Kris Jusiak.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <experimental/reflect>
#include <iostream>
#include <string_view>
#include <utility>

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
struct arg {
  static constexpr auto name = Name;
  TValue value{};

  template <class T>
  auto operator=(T t) const {
    return arg<Name, T>{.value = t};
  }
};

namespace meta = std::experimental::reflect;

template <fixed_string Name>
struct fn {
  template <class T>
  auto operator()(T& obj, auto... args) {
    [&]<class... Ts>(std::tuple<Ts...>) {
      const auto f = [&]<class U> {
        if constexpr (std::string_view{Name} ==
                      std::string_view{meta::get_name_v<U>}) {
          [&]<class TParams, auto... Ns>(TParams, std::index_sequence<Ns...>) {
            const auto get_arg = [&]<class P>(P) {
              return ([&] -> meta::get_reflected_type_t<meta::get_type_t<P>> {
                if constexpr (std::string_view{meta::get_name_v<P>} ==
                              std::string_view{args.name}) {
                  return args.value;
                } else {
                  return {};
                }
              }() + ...);
            };
            (obj.*meta::get_pointer_v<U>)(get_arg(
                meta::get_element_t<Ns, TParams>{})...);
          }
          (meta::get_parameters_t<U>{},
           std::make_index_sequence<
               meta::get_size_v<meta::get_parameters_t<U>>>{});
        }
      };
      (f.template operator()<Ts>(), ...);
    }
    (meta::unpack_sequence_t<std::tuple,
                             meta::get_member_functions_t<reflexpr(T)>>{});
  }
};

template <fixed_string Name>
auto operator""_arg() {
  return arg<Name>{};
}
template <fixed_string Name>
auto operator""_fn() {
  return fn<Name>{};
}

struct foo {
  auto bar(int value) { std::cout << "bar: " << value << '\n'; }
  auto baz(int i, double d = 42.0) {
    std::cout << "baz: " << i << ", " << d << '\n';
  }
};

int main() {
  foo f{};
  "bar"_fn(f, "value"_arg = 42);            // prints bar: 42
  "baz"_fn(f, "i"_arg = 4, "d"_arg = 2.0);  // prints baz: 4, 2
  "baz"_fn(f, "d"_arg = 0., "i"_arg = 42);  // prints baz: 42, 0
}
