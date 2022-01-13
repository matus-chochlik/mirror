/// @example mirror/expression.cpp
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///
#include <mirror/primitives.hpp>
#include <cmath>
#include <iostream>
//------------------------------------------------------------------------------
struct foo {
    foo(int, int) {}

    friend auto operator<<(std::ostream& out, const foo) -> std::ostream& {
        return out << "foo";
    }
};
//------------------------------------------------------------------------------
int main() {
    const auto msfe = mirror((std::asin(1.F)));
    const auto msde = mirror((std::asin(1.0)));
    const auto mfce = mirror((foo(1, 1)));

    static_assert(reflects_parenthesized_expression(msfe));
    static_assert(reflects_parenthesized_expression(msde));
    static_assert(reflects_parenthesized_expression(mfce));

    const auto msf = get_callable(get_subexpression(msfe));
    const auto msd = get_callable(get_subexpression(msde));
    const auto mfc = get_callable(get_subexpression(mfce));

    static_assert(reflects_function(msf));
    static_assert(reflects_function(msd));
    static_assert(reflects_constructor(mfc));

    static_assert(!reflects_same(msf, msd));

    std::cout << invoke(msf, 1.0F) << std::endl;
    std::cout << invoke(msd, 0.50) << std::endl;
    std::cout << invoke(mfc, 4, 5) << std::endl;

    return 0;
}
