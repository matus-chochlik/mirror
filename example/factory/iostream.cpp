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

    using iostream_factory_builder = factory_builder<iostream_factory_traits>;

    auto fac = iostream_factory_builder("iof").build<test::tetrahedron>();
    auto teh = fac.construct({std::cin, std::cout});

    std::cout << "volume of the tetrahedron is: " << teh.volume() << std::endl;
    std::cout << "area of its base is: " << teh.base().area() << std::endl;
    std::cout << "distance of its apex from origin is: "
              << teh.apex().direction().length() << std::endl;

    return 0;
}
