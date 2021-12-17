/// @example invoke.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <iostream>
#include <mirror/primitives.hpp>
//------------------------------------------------------------------------------
class myclass {
public:
    constexpr myclass() noexcept = default;
    myclass(int j) noexcept
      : _j{j} {}
    ~myclass() noexcept = default;

    static void foo() {}
    constexpr bool bar() const {
        return false;
    }
    static int baz(int a, int b) noexcept {
        return a + b;
    }
    int operator+(int i) const noexcept {
        return _j + i;
    }

private:
    int _j{0};
};
//------------------------------------------------------------------------------
int main() {
    const myclass x;
    const auto mmc = mirror(myclass);
    std::cout << get_name(mmc) << std::endl;

    invoke_on(get_element<0>(get_member_functions(mmc)), x);
    std::cout << invoke_on(get_element<1>(get_member_functions(mmc)), x)
              << std::endl;
    std::cout << invoke_on(get_element<2>(get_member_functions(mmc)), x, 5, 5)
              << std::endl;

    invoke(get_element<0>(get_member_functions(mmc)));
    std::cout << invoke(get_element<1>(get_member_functions(mmc)), x)
              << std::endl;
    std::cout << invoke(get_element<2>(get_member_functions(mmc)), 21, 21)
              << std::endl;

    const auto y = invoke(get_element<1>(get_constructors(mmc)), 4);

    std::cout << invoke(get_element<0>(get_operators(mmc)), y, 3) << std::endl;

    return 0;
}
