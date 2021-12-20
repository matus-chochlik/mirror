/// @example mirror/row_polymorphism.cpp
///
/// Copyright Kris Jusiak
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <experimental/mirror>
#include <experimental/reflect>
#include <iostream>
#include <memory>
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

namespace detail {
template <fixed_string Name, class TIf, class TImpl>
struct bind {
  static constexpr auto name = Name;
  using if_t = TIf;
  using impl_t = TImpl;
};
}  // namespace detail

template <class TIf, class TImpl>
auto bind() {
  return detail::bind<"", TIf, TImpl>{};
}
template <fixed_string Name, class TImpl>
auto bind() {
  return detail::bind<Name, TImpl, TImpl>{};
}

namespace meta = std::experimental::reflect;

template <class... TWirings>
struct injector : TWirings... {
  explicit(true) constexpr injector(TWirings...) {}

  template <class T>
  constexpr auto create() const {
    return [this]<class... Ts>(std::tuple<Ts...>) {
      const auto wiring = [this]<class TName, class TParam>(
                              TName, TParam) -> decltype(auto) {
        constexpr auto has_type_wiring = []<class TWiring>(TWiring) {
          return std::is_same_v<std::remove_cvref_t<meta::get_reflected_type_t<
                                    meta::get_type_t<TParam>>>,
                                typename TWiring::if_t>;
        };
        constexpr auto has_named_wiring = []<class TWiring>(TWiring) {
          return std::string_view{TWiring::name}.substr(
                     0, std::size(std::string_view{meta::get_name_v<TName>})) ==
                     meta::get_name_v<TName> and
                 std::string_view{TWiring::name}.substr(
                     std::size(std::string_view{meta::get_name_v<TName>}) +
                     1) == meta::get_name_v<TParam>;
        };

        static_assert(
            ((has_type_wiring(TWirings{}) or has_named_wiring(TWirings{})) or
             ...),
            "Missing wiring!");
        static std::shared_ptr<std::remove_cvref_t<
            meta::get_reflected_type_t<meta::get_type_t<TParam>>>>
            param{};
        (
            [&] {
              if constexpr (has_named_wiring(TWirings{})) {
                param = std::make_shared<typename TWirings::impl_t>();
              } else if constexpr (has_type_wiring(TWirings{})) {
                param = std::make_shared<typename TWirings::impl_t>();
              }
            }(),
            ...);
        return *param;
      };

      return (
          [&]<class TName, class... TParams>(TName, std::tuple<TParams...>) {
            return T{wiring(TName{}, TParams{})...};
          }(Ts{},
            meta::unpack_sequence_t<std::tuple, meta::get_parameters_t<Ts>>{}),
          ...);
    }
    (meta::unpack_sequence_t<std::tuple,
                             meta::get_constructors_t<reflexpr(T)>>{});
  }
};

// clang-format off
int main() {
  struct interface {
    virtual ~interface() noexcept = default;
    virtual int get() const = 0;
  };

  struct implementation1 : interface {
    int get() const override { return 1; }
  };
  struct implementation2 : interface {
    int get() const override { return 2; }
  };

  struct dependency_injection {
    explicit(true) dependency_injection(const interface& i1, const interface& i2) : i1{i1}, i2{i2} { }

    auto run() {
      std::cout << i1.get() << ", " << i2.get();
      return 0;
    }

   private:
    const interface& i1;
    const interface& i2;
  };

  const auto wiring = injector{
      bind<interface,                 implementation1>(), // binds any interface parameter to implementation1
      bind<"dependency_injection.i2", implementation2>()  // overwrites binding for dependency_injection.i parameter to implementation2
  };

  auto di = wiring.create<dependency_injection>();
  return di.run();  // prints 1, 2
}
// clang-format on
