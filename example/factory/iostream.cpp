/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#include <mirror/factory/builder.hpp>
#include <mirror/factory/iostream.hpp>
#include <mirror/testdecl.hpp>

int main() {
    using namespace mirror;

    using iostream_factory_builder =
      factory_builder<iostream_factory_traits, test::point>;
    auto f = iostream_factory_builder("iof", std::cin, std::cout).build();

    auto p = f.construct();

    std::cout << p.x() << ", " << p.y() << ", " << p.z() << std::endl;
    return 0;
}
