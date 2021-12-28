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
int main() {
    const auto msfe = mirror((std::asin(1.F)));
    const auto msde = mirror((std::asin(1.0)));

    static_assert(reflects_parenthesized_expression(msfe));
    static_assert(reflects_parenthesized_expression(msde));

    const auto msf = get_callable(get_subexpression(msfe));
    const auto msd = get_callable(get_subexpression(msde));

    static_assert(reflects_function(msf));
    static_assert(reflects_function(msd));

    static_assert(!reflects_same(msf, msd));

    std::cout << invoke(msf, 1.F) << std::endl;
    std::cout << invoke(msd, 1.0) << std::endl;

    return 0;
}
